defmodule NifSendSampleTest do
  use ExUnit.Case
  doctest NifSendSample

  test "send_nif(self(), :ping)" do
    refute_receive(:ping, 100)
    NifSendSample.send_nif(self(), :ping)
    assert_receive(:ping, 1_000)
  end
end
