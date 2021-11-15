/****************************************************************************
 *
 *   Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file FlightTaskAutoLineSmoothVel.hpp
 *
 * Flight task for autonomous, gps driven mode. The vehicle flies
 * along a straight line in between waypoints.
 */

#pragma once

#include "FlightTaskAuto.hpp"

class FlightTaskAutoLineSmoothVel : public FlightTaskAuto
{
public:
	FlightTaskAutoLineSmoothVel() = default;
	virtual ~FlightTaskAutoLineSmoothVel() = default;

	bool activate(const vehicle_local_position_setpoint_s &last_setpoint) override;
	void reActivate() override;
	bool update() override;

protected:

	/** Reset position or velocity setpoints in case of EKF reset event */
	void _ekfResetHandlerPositionXY(const matrix::Vector2f &delta_xy) override;
	void _ekfResetHandlerVelocityXY(const matrix::Vector2f &delta_vxy) override;
	void _ekfResetHandlerPositionZ(float delta_z) override;
	void _ekfResetHandlerVelocityZ(float delta_vz) override;
	void _ekfResetHandlerHeading(float delta_psi) override;

	void _generateSetpoints(); /**< Generate setpoints along line. */
	void _generateHeading();
	void _checkEmergencyBraking();
	bool _generateHeadingAlongTraj(); /**< Generates heading along trajectory. */


	bool isTargetModified() const;

	void _prepareSetpoints(); /**< Generate velocity target points for the trajectory generator. */
	void _updateTrajConstraints();

	/** determines when to trigger a takeoff (ignored in flight) */
	bool _checkTakeoff() override { return _want_takeoff; };

	void _prepareIdleSetpoints();
	void _prepareLandSetpoints();
	void _prepareVelocitySetpoints();
	void _prepareTakeoffSetpoints();
	void _preparePositionSetpoints();
	bool _highEnoughForLandingGear(); /**< Checks if gears can be lowered. */

	void updateParams() override; /**< See ModuleParam class */
};
