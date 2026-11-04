#ifndef CHOOKS_STATIC_H
# define CHOOKS_STATIC_H

# include <sys/mman.h>

# include "chooks/utils.h"

# define MAKE_SIG(Count, Types) EVAL_GLUE(SIG_, Count) Types
# define MAKE_CALL(Count) EVAL_GLUE(CALL_, Count)
# define MAKE_ARRAY(Count) EVAL_GLUE(ARRAY_, Count)

# define INIT_HOOK(RetType, FuncName, ArgTypes)                                \
__attribute__((weak)) hook_info_t FuncName##_hook_info = {                     \
  .func_name = #FuncName,                                                      \
  .main = NULL,                                                                \
  .pre = NULL,                                                                 \
  .pre_count = 0,                                                              \
  .post = NULL,                                                                \
  .post_count = 0 };                                                           \
                                                                               \
__attribute__((weak)) RetType (*real_##FuncName) ArgTypes = NULL;              \
                                                                               \
static void init_##FuncName##_hooks() {                                        \
	size_t page_size = sysconf(_SC_PAGESIZE);
	unsigned char *trampoline = (unsigned char *)mmap(NULL, page_size,
			PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	void *page_start = (void *)((uintptr_t)
}                                                                              \
                                                                               \
__attribute__((weak))                                                          \
RetType FuncName ( MAKE_SIG( ARGS_COUNT ArgTypes, ArgTypes ) ) {               \
  static RetType (*real_func) ArgTypes = NULL;                                 \
  if (!real_##FuncName) {                                                      \
    real_##FuncName = dlsym(RTLD_NEXT, #FuncName);                             \
  }                                                                            \
  void *args = MAKE_ARRAY(ARGS_COUNT ArgTypes);                                \
  for (int i = 0; i < FuncName##_hook_info.pre_count; i++) {                   \
    if (FuncName##_hook_info.pre[i]) {                                         \
      FuncName##_hook_info.pre[i](args);                                       \
    }                                                                          \
  }                                                                            \
  RetType result;                                                              \
  if (!FuncName##_hook_info.main) {                                            \
    result = real_##FuncName ( MAKE_CALL( ARGS_COUNT ArgTypes ) );             \
  } else {                                                                     \
    FuncName##_hook_info.main(args, (void*)&result);                           \
  }                                                                            \
  for (int i = 0; i < FuncName##_hook_info.post_count; i++) {                  \
    if (FuncName##_hook_info.post[i]) {                                        \
      FuncName##_hook_info.post[i](args, (void*)&result);                      \
    }                                                                          \
  }                                                                            \
  return result;                                                               \
}

#endif /* end of: CHOOKS_STATIC_H
*/
