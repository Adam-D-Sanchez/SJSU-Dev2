#include "L2_HAL/displays/led/onboard_led.hpp"
#include "L4_Testing/testing_frameworks.hpp"

EMIT_ALL_METHODS(OnBoardLed);

TEST_CASE("OnBoardLed Test", "[onboard_led]")
{

  // These represent the expected values of led_states_test after each test
  constexpr uint8_t kLedStatesExpectedOn     = 0b0000'0001;
  constexpr uint8_t kLedStatesExpectedOff    = 0b0000'0000;
  constexpr uint8_t kLedStatesExpectedSet    = 0b0000'0010;
  constexpr uint8_t kLedStatesExpectedToggle = 0b0000'0110;
  constexpr uint8_t kLedStatesExpectedSetAll = 0b0000'1111;

    // Creating an object to be tested. The object is then intialized.
  LPC_IOCON_TypeDef local_iocon;
  memset(&local_iocon, 0, sizeof(local_iocon));
  Pin::pin_map = reinterpret_cast<Pin::PinMap_t *>(&local_iocon);
  LPC_GPIO_TypeDef led_local_port[4];
  memset(&led_local_port, 0, sizeof(led_local_port));

  Gpio::gpio_port[0] = &led_local_port[0];
  Gpio::gpio_port[1] = &led_local_port[1];
  Gpio::gpio_port[2] = &led_local_port[2];
  Gpio::gpio_port[3] = &led_local_port[3];


  Gpio p02_03(2, 3);
  Gpio p01_26(1, 26);
  Gpio p01_24(1, 24);
  Gpio p01_18(1, 18);

  OnBoardLed led_control_test_unit;
  led_control_test_unit.Initialize();
  SECTION("Initialize")
  {
  }
  SECTION("Turning On and Off the LEDs.")
  {
    led_control_test_unit.On(0);
    CHECK(kLedStatesExpectedOn == led_control_test_unit.GetStates());
    led_control_test_unit.Off(0);
    CHECK(kLedStatesExpectedOff == led_control_test_unit.GetStates());
    led_control_test_unit.Set(1, OnBoardLedInterface::LightState::kOn);
    CHECK(kLedStatesExpectedSet == led_control_test_unit.GetStates());
    led_control_test_unit.Toggle(2);
    CHECK(kLedStatesExpectedToggle == led_control_test_unit.GetStates());
    led_control_test_unit.SetAll(0x0F);
    CHECK(kLedStatesExpectedSetAll == led_control_test_unit.GetStates());

    // This is done to turn off all the LEDs before being in use.
    led_control_test_unit.SetAll(0x00);
  }
}
