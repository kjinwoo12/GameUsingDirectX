#include "CameraClass.h"
#include <stdio.h>


CameraClass::CameraClass() {
	m_position = D3DXVECTOR3(0, 0, -1);
	m_rotation = D3DXVECTOR3(0, 0, 0);
	m_fixedMatrix = D3DXMATRIX(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 1.f, 1.f
	);
}


CameraClass::~CameraClass() {
}


void CameraClass::setPosition(float x, float y, float z) {
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	return;
}

void CameraClass::setRotation(float x, float y, float z) {
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	return;
}


D3DXVECTOR3 CameraClass::getPosition() {
	return m_position;
}


D3DXVECTOR3 CameraClass::getRotation() {
	return m_rotation;
}


void CameraClass::render() {
	D3DXVECTOR3 up, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = m_rotation.x;
	yaw = m_rotation.y;
	roll = m_rotation.z;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt = m_position + lookAt;

	D3DXMatrixLookAtLH(&m_viewMatrix, &m_position, &lookAt, &up);
	return;
}


void CameraClass::getViewMatrix(D3DXMATRIX& viewMatrix) {
	viewMatrix = m_viewMatrix;
}


void CameraClass::getFixedMatrix(D3DXMATRIX& fixedMatrix) {
	fixedMatrix = m_fixedMatrix;
}