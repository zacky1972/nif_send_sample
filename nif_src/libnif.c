#include <erl_nif.h>

static ERL_NIF_TERM send_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
    return enif_make_atom(env, "ok");
}

static ErlNifFunc nif_funcs [] =
{
    {"send_nif", 2, send_nif},
};

ERL_NIF_INIT(Elixir.NifSendSample, nif_funcs, NULL, NULL, NULL, NULL)