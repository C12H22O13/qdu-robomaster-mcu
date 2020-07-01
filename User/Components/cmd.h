/* 
	控制命令
*/

#pragma once

#include "user_math.h"
#include "ahrs.h"

/*  
	CHASSIS_MODE_RELAX: No force applied. For all robot when power on.
	CHASSIS_MODE_BREAK: Set to zero speed. Force applied. For all robot when break.
	CHASSIS_MODE_FOLLOW_GIMBAL: Follow gimbal by follow encoder. For infantry, hero and engineer.
	CHASSIS_MODE_ROTOR: Constantly rotating. For infantry and hero.
	CHASSIS_MODE_INDENPENDENT: Run independently. For sentry and drone.
	CHASSIS_MODE_OPEN: Direct apply force without pid control. For TEST only.
*/
typedef enum {
	CHASSIS_MODE_RELAX, 
	CHASSIS_MODE_BREAK,
	CHASSIS_MODE_FOLLOW_GIMBAL,
	CHASSIS_MODE_ROTOR,
	CHASSIS_MODE_INDENPENDENT,
	CHASSIS_MODE_OPEN,
} CMD_Chassis_Mode_t;

/*  
	GIMBAL_MODE_RELAX: No force applied.
	GIMBAL_MODE_INIT: .
	GIMBAL_MODE_CALI: Get mid point.
	GIMBAL_MODE_ABSOLUTE: Follow IMU data.
	GIMBAL_MODE_RELATIVE: Follow encoder data.
	GIMBAL_MODE_FIX: Set to a fix angle. Force applied.
*/
typedef enum {
	GIMBAL_MODE_RELAX,
	GIMBAL_MODE_INIT,
	GIMBAL_MODE_CALI,
	GIMBAL_MODE_ABSOLUTE,
	GIMBAL_MODE_RELATIVE,
	GIMBAL_MODE_FIX,
} CMD_Gimbal_Mode_t;

/*  
	SHOOT_MODE_RELAX: No force applied.
	SHOOT_MODE_SAFE: Set to zero speed. Force applied.
	SHOOT_MODE_STDBY: Ready to switch to FIRE.
	SHOOT_MODE_FIRE: Ready to shoot.
*/
typedef enum {
	SHOOT_MODE_RELAX,
	SHOOT_MODE_SAFE,
	SHOOT_MODE_STDBY,
	SHOOT_MODE_FIRE,
} CMD_Shoot_Mode_t;

typedef struct {
	CMD_Chassis_Mode_t mode;
	MoveVector_t ctrl_v;
} CMD_Chassis_Ctrl_t;

typedef struct {
	CMD_Gimbal_Mode_t mode;
	AHRS_Eulr_t eulr;
} CMD_Gimbal_Ctrl_t;

typedef struct {
	CMD_Shoot_Mode_t mode;
	float32_t bullet_speed;
	float32_t shoot_freq_hz;
} CMD_Shoot_Ctrl_t;

typedef struct {
	CMD_Chassis_Ctrl_t chassis;
	CMD_Gimbal_Ctrl_t gimbal;
	CMD_Shoot_Ctrl_t shoot;
} CMD_t;

typedef enum {
	CMD_SW_ERR = 0,
	CMD_SW_UP = 1,
	CMD_SW_MID = 3,
	CMD_SW_DOWN = 2,
} CMD_SwitchPos_t;

typedef enum {
	DR16_KEY_W = 0,
	DR16_KEY_S,
	DR16_KEY_A,
	DR16_KEY_D,
	DR16_KEY_Q,
	DR16_KEY_E,
	DR16_KEY_SHIFT,
	DR16_KEY_CTRL,
} CMD_KeyValue_t;

typedef struct {
	float32_t ch_l_x;
	float32_t ch_l_y;
	float32_t ch_r_x;
	float32_t ch_r_y;
	
	float32_t ch_res;
	
	CMD_SwitchPos_t sw_l;
	CMD_SwitchPos_t sw_r;
	
	struct {
		int16_t x;
		int16_t y;
		int16_t z;
		bool l_click;
		bool r_click;
	} mouse;
	
	uint16_t key;
	uint16_t res;
} CMD_RC_t;

bool CMD_KeyPressed(const CMD_RC_t *rc, CMD_KeyValue_t key);
int8_t CMD_Parse(const CMD_RC_t *rc, CMD_t *cmd);
