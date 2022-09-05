defmodule NifSendSampleTest do
  use ExUnit.Case
  doctest NifSendSample

  test "send_nif(self(), :ping)" do
    refute_receive(:ping, 100)
    NifSendSample.send_nif(self(), :ping)
    assert_receive(:ping, 1_000)
  end

  test "spawn send_nif" do
    refute_receive(:pong, 100)
    pid = self()
    spawn(fn -> NifSendSample.send_nif(pid, :pong) end)
    assert_receive(:pong, 1_000)
  end

  test "send_nif_threaded(self(), :ok)" do
    refute_receive(:ok, 100)
    NifSendSample.send_nif_threaded(self(), :ok)
    assert_receive(:ok, 1_000)
  end

  test "spawn send_nif_threaded" do
    refute_receive(:ping, 100)
    pid = self()
    spawn(fn -> NifSendSample.send_nif_threaded(pid, :ping) end)
    assert_receive(:ping, 1_000)
  end
end
