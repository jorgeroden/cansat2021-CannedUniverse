#include "MPU9250.h" //hideakitai library

MPU9250 mpu;

void initMPU() {

  if (!mpu.setup(0x68)) {  // change to your own address
    Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
  }
}

String getYPR() {//Yaw/Pitch/Roll

  return String(mpu.getYaw(), 2) + "," + String(mpu.getPitch(), 2) + "," + String(mpu.getRoll(), 2);

}

String getAcc() {

  return String(mpu.getAccX(), 2) + "," + String(mpu.getAccY(), 2) + "," + String(mpu.getAccZ(), 2);
}
