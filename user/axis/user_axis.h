/**
 * @file user/axis/user_axis.h
 *
 * @author Hiroyuki Chishiro
 */

void test_integer_instructions(void);
void test_transfer_instructions(void);
void test_control_instructions(void);
void test_special_instructions(void);

void cluster_main(void);

void *user_func(void *arg);
int user_thread_main(void);
void timer_main(void);
int dmac_main(void);
int test_main(void);
void callback_func(void);
void callback_main(void);
void multi_cpus_main(void);
void tsc_main(void);



