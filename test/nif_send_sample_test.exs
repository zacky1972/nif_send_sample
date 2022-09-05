defmodule NifSendSampleTest do
  use ExUnit.Case
  doctest NifSendSample

  test "send_nif(self(), :ping)" do
    refute_receive(:ping, 100)
    NifSendSample.send_nif(self(), :ping)
    assert_receive(:ping, 1_000)
  end

  test "spawn send_nif" do
    refute_receive(:ping, 100)
    pid = self()
    spawn(fn -> NifSendSample.send_nif(pid, :ping) end)
    assert_receive(:ping, 1_000)
  end
end
