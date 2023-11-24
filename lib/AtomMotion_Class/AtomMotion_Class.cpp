#include "AtomMotion_Class.hpp"

namespace m5
{
  bool AtomMotion::writeRegister16(std::uint8_t reg, std::uint16_t data)
  {
    std::uint8_t buf[2] = {(uint8_t)(data >> 8), (uint8_t)(data & 0xFF)};
    return writeRegister(reg, buf, sizeof(buf));
  }

  std::uint16_t AtomMotion::readRegister16(std::uint8_t reg)
  {
    std::uint8_t buf[2];
    readRegister(reg, buf, sizeof(buf));
    std::uint16_t result = (((std::uint16_t)buf[0]) << 8) | buf[1];
    return result;
  }

  /*******************************************************************************/

  // Servo(1~4)
  // angle: 0-180
  std::uint8_t AtomMotion::SetServoAngle(std::uint8_t Servo_CH, std::uint8_t angle)
  {
    std::uint8_t Register_address = Servo_CH - 1;
    if (Register_address > 3) return 0;
    writeRegister8(Register_address, (std::uint8_t)angle);
    return 0;
  }

  // Servo(1~4)
  // pulse: 500-2500
  std::uint8_t AtomMotion::SetServoPulse(std::uint8_t Servo_CH, std::uint16_t width)
  {
    std::uint8_t servo_ch         = Servo_CH - 1;
    std::uint8_t Register_address = 2 * servo_ch + 16;
    if (Register_address % 2 == 1 || Register_address > 32) return 1;
    writeRegister16(Register_address, width);
    return 0;
  }

  // Motor(1~2)
  // speed: -127-127
  std::uint8_t AtomMotion::SetMotorSpeed(std::uint8_t Motor_CH, std::int8_t speed)
  {
    std::uint8_t servo_ch = Motor_CH - 1;
    if (servo_ch > 1) return 1;
    std::uint8_t Register_address = servo_ch + 32;
    writeRegister8(Register_address, (std::uint8_t)speed);
    return 0;
  }

  std::uint8_t AtomMotion::ReadServoAngle(std::uint8_t Servo_CH)
  {
    std::uint8_t Register_address = Servo_CH - 1;
    return readRegister8(Register_address);
  }

  std::uint16_t AtomMotion::ReadServoPulse(std::uint8_t Servo_CH)
  {
    std::uint8_t servo_ch         = Servo_CH - 1;
    std::uint8_t Register_address = 2 * servo_ch | 0x10;
    return readRegister16(Register_address);
  }

  std::int8_t AtomMotion::ReadMotorSpeed(std::uint8_t Motor_CH)
  {
    std::int8_t data      = 0;
    std::uint8_t servo_ch = Motor_CH - 1;
    if (servo_ch > 1) return 1;
    std::uint8_t Register_address = servo_ch | 0x20;
    return readRegister8(Register_address);
  }
}
