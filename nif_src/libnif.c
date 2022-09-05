#include <stdbool.h>
#include <erl_nif.h>

static ERL_NIF_TERM send_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    if(__builtin_expect(argc != 2, false)) {
        return enif_make_badarg(env);
    }

    ErlNifPid pid;
    if(__builtin_expect(!enif_get_local_pid(env, argv[0], &pid), false)) {
        return enif_make_badarg(env);
    }

    ErlNifEnv *msg_env = enif_alloc_env();
    if(__builtin_expect(msg_env == NULL, false)) {
        return enif_make_badarg(env);
    }
    ERL_NIF_TERM message = argv[1];
    if(__builtin_expect(!enif_send(NULL, &pid, msg_env, message), false)) {
        return enif_make_tuple2(env, enif_make_atom(env, "error"), enif_make_string(env, "Fail to send.", ERL_NIF_LATIN1));
    }

    return enif_make_atom(env, "ok");
}

void *send_nif_threaded_sub(void *args)
{
    ErlNifEnv *msg_env = enif_alloc_env();
    ERL_NIF_TERM *tuple = (ERL_NIF_TERM *)args;
    int arity;
    const ERL_NIF_TERM *array;
    enif_get_tuple(msg_env, *tuple, &arity, &array);
    if(__builtin_expect(arity != 2, false)) {
        return NULL;
    }
    ErlNifPid pid;
    enif_get_local_pid(msg_env, array[0], &pid);
    enif_send(NULL, &pid, msg_env, array[1]);
    return NULL;
}

static ERL_NIF_TERM send_nif_threaded(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    if(__builtin_expect(argc != 2, false)) {
        return enif_make_badarg(env);
    }

    ERL_NIF_TERM tuple = enif_make_tuple2(env, argv[0], argv[1]);

    ErlNifTid tid;
    if(__builtin_expect(enif_thread_create("send_nif_threaded_sub", &tid, send_nif_threaded_sub, &tuple, NULL), false)) {
        return enif_make_badarg(env);
    }

    return enif_make_atom(env, "ok");    
}

static ErlNifFunc nif_funcs [] =
{
    {"send_nif", 2, send_nif},
    {"send_nif_threaded", 2, send_nif_threaded},
};

ERL_NIF_INIT(Elixir.NifSendSample, nif_funcs, NULL, NULL, NULL, NULL)