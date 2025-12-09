#ifndef AUTH_H
#define AUTH_H

/* Authentication module
   - admin_login(): prompts for admin password, returns 1 on success, 0 on fail
   - student_login(roll): prompts for roll and copies into provided buffer; returns 1 (always success for prompt)
*/

int admin_login(void);
/* student_login fills 'roll' buffer (should be at least 16 chars) */
int student_login(char *roll);

#endif /* AUTH_H */
