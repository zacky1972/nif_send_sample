defmodule NifSendSampleTest do
  use ExUnit.Case
  doctest NifSendSample

  test "greets the world" do
    assert NifSendSample.hello() == :world
  end
end
