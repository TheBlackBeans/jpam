#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_ext.h>
#include <security/pam_modules.h>
#include "challenge_gen.h"
#include "security/_pam_types.h"
#include "string.h"

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  printf("Acct mgmt\n");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  const char *result;
  j_challenge *chal = gen_challenge();
  string *prompt = of_str("Process this: ");
  extend_string(prompt, chal->code);
  int retval = pam_get_authtok(pamh, PAM_AUTHTOK, &result, prompt->ptr);
  drop(prompt);
  if (retval != PAM_SUCCESS) {
    drop_chal(chal);
    return retval;
  }
  if (atoi(result) != chal->solution) {
    drop_chal(chal);
    return PAM_AUTH_ERR;
  }
  drop_chal(chal);
  return PAM_SUCCESS;
}
