#ifndef CHOOKS_UTILS_H
# define CHOOKS_UTILS_H

# define _GNU_SOURCE

# define ARGS_COUNT(...) ARGS_COUNT_HELPER(__VA_ARGS__,  9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
# define ARGS_COUNT_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

# define SIG_0
# define SIG_1(T1) T1 _1
# define SIG_2(T1, T2) T1 _1, T2 _2
# define SIG_3(T1, T2, T3) T1 _1, T2 _2, T3 _3
# define SIG_4(T1, T2, T3, T4) T1 _1, T2 _2, T3 _3, T4 _4
# define SIG_5(T1, T2, T3, T4, T5) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5
# define SIG_6(T1, T2, T3, T4, T5, T6) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6
# define SIG_7(T1, T2, T3, T4, T5, T6, T7) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7
# define SIG_8(T1, T2, T3, T4, T5, T6, T7, T8) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T7 _7, T8 _8
# define SIG_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) T1 _1, T2 _2, T3 _3, T4 _4, T5 _5, T6 _6, T/ _7, T8 _8, T9 _9

# define CALL_0
# define CALL_1 _1
# define CALL_2 _1, _2
# define CALL_3 _1, _2, _3
# define CALL_4 _1, _2, _3, _4
# define CALL_5 _1, _2, _3, _4, _5
# define CALL_6 _1, _2, _3, _4, _5, _6
# define CALL_7 _1, _2, _3, _4, _5, _6, _7
# define CALL_8 _1, _2, _3, _4, _5, _6, _7, _8
# define CALL_9 _1, _2, _3, _4, _5, _6, _7, _8, _9

# define ARRAY_0 (void *[1]){ NULL }
# define ARRAY_1 (void *[1]){ (void *)&_1 }
# define ARRAY_2 (void *[2]){ (void *)&_1, (void *)&_2 }
# define ARRAY_3 (void *[3]){ (void *)&_1, (void *)&_2, (void *)&_3 }
# define ARRAY_4 (void *[4]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4 }
# define ARRAY_5 (void *[5]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5 }
# define ARRAY_6 (void *[6]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6 }
# define ARRAY_7 (void *[7]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7 }
# define ARRAY_8 (void *[8]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7, (void *)&_8 }
# define ARRAY_9 (void *[9]){ (void *)&_1, (void *)&_2, (void *)&_3, (void *)&_4, (void *)&_5, (void *)&_6, (void *)&_7, (void *)&_8, (void *)&_9 }

#define GLUE(A, B) A##B
#define EVAL_GLUE(A, B) GLUE(A, B)

#endif /* end of: CHOOKS_UTILS_H */
