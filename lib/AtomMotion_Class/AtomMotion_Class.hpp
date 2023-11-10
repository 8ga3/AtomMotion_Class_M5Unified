#ifndef __ATOM_MOTION_CLASS_H__
#define __ATOM_MOTION_CLASS_H__

#include "utility/I2C_Class.hpp"

namespace m5
{
  class AtomMotion : public I2C_Device
  {
    private:
    bool writeRegister16(std::uint8_t reg, std::uint16_t data);
    std::uint16_t readRegister16(std::uint8_t reg);

    public:
      static constexpr std::uint8_t DEFAULT_ADDRESS = 0x38;

      AtomMotion(std::uint8_t i2c_addr = DEFAULT_ADDRESS, std::uint32_t freq = 400000, I2C_Class* i2c = &In_I2C)
      : I2C_Device ( i2c_addr, freq, i2c )
      {}

      std::uint8_t SetServoAngle(std::uint8_t Servo_CH, std::uint8_t angle);

      std::uint8_t SetServoPulse(std::uint8_t Servo_CH, std::uint16_t width);

      std::uint8_t SetMotorSpeed(std::uint8_t Motor_CH, std::int8_t speed);

      std::uint8_t ReadServoAngle(std::uint8_t Servo_CH);

      std::uint16_t ReadServoPulse(std::uint8_t Servo_CH);

      std::int8_t ReadMotorSpeed(std::uint8_t Motor_CH);
  };
}

#endif
