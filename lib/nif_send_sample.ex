defmodule NifSendSample do
  require Logger

  @moduledoc """
  Documentation for `NifSendSample`.
  """

  @on_load :load_nif

  @doc false
  def load_nif do
    nif_file = ~c'#{Application.app_dir(:nif_send_sample, "priv/libnif")}'

    case :erlang.load_nif(nif_file, 0) do
      :ok -> :ok
      {:error, {:reload, _}} -> :ok
      {:error, reason} -> Logger.error("Failed to load NIF: #{inspect(reason)}")
    end
  end

  def send_nif(_pid, _message), do: :erlang.nif_error(:not_loaded)

  @doc """
  Hello world.

  ## Examples

      iex> NifSendSample.hello()
      :world

  """
  def hello do
    :world
  end
end
