#ifndef BILLING_H
#define BILLING_H

/* Billing module API */

/* Calculate and print monthly bill for individual student (prints to stdout). */
void calculate_monthly_bill_individual(const char *roll);

/* Generate admin monthly summary report (prints to stdout),
   optionally writes summary to a billing file if implemented. */
void generate_monthly_report(void);

/* Optionally: settle student's due by deducting/adding amount (returns 1 on success) */
int adjust_student_balance(const char *roll, double amount, const char *reason);

#endif /* BILLING_H */
