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

static ErlNifFunc nif_funcs [] =
{
    {"send_nif", 2, send_nif},
};

ERL_NIF_INIT(Elixir.NifSendSample, nif_funcs, NULL, NULL, NULL, NULL)