#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	VPBuffer = make_unique<ViewProjectionBuffer>();

	eye = { position.x, position.y, 0 };
	at = { position.x, position.y, 1 };

	view = XMMatrixLookAtLH(eye, at, up);
	proj = XMMatrixOrthographicOffCenterLH(LB.x, RT.x, LB.y, RT.y, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(proj);
}

Camera::~Camera() {}

void Camera::Update()
{
	//카메라 수동 조작
}

void Camera::Render()
{
	VPBuffer->SetVSBuffer(1);
}

void Camera::UpdateView()
{

	eye = { position.x, position.y, 0 };
	at = { position.x, position.y, 1 };

	view = XMMatrixLookAtLH(eye, at, up);

	VPBuffer->SetView(view);
}

void Camera::UpdateProj()
{
	proj = XMMatrixOrthographicOffCenterLH(LB.x, RT.x, LB.y, RT.y, 0, 1);

	VPBuffer->SetProjection(proj);
}

void Camera::ZoomIn()
{
	if (LB.y + zoomSpeed * TIME->GetDeltaTime() * 3 >= RT.y - zoomSpeed * TIME->GetDeltaTime() * 3)   return;
	LB.x += zoomSpeed * TIME->GetDeltaTime() * widthRatio;
	LB.y += zoomSpeed * TIME->GetDeltaTime();
	RT.x -= zoomSpeed * TIME->GetDeltaTime() * widthRatio;
	RT.y -= zoomSpeed * TIME->GetDeltaTime();

	UpdateProj();
}

void Camera::ZoomOut()
{
	LB.x -= zoomSpeed * TIME->GetDeltaTime() * widthRatio;
	LB.y -= zoomSpeed * TIME->GetDeltaTime();
	RT.x += zoomSpeed * TIME->GetDeltaTime() * widthRatio;
	RT.y += zoomSpeed * TIME->GetDeltaTime();

	UpdateProj();
}

void Camera::InitZoom()
{
	LB = { 0, 0 };
	RT = { WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT };

	UpdateProj();
}

Vector2 Camera::UnProject(const Vector2& source)
{
	Vector2 output;

	output = (source / Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT) * 2.0f) - Vector2(1, 1);

	Matrix VPInverse = (view * proj).Invert();

	return XMVector2TransformCoord(output, VPInverse);
}

void Camera::SetPosition(const Vector2& position)
{
	this->position = position;

	if (bEdge)
	{
		if (this->position.x < minEdge.x)
			this->position.x = minEdge.x;
		else if (this->position.x + WIN_DEFAULT_WIDTH > maxEdge.x)
			this->position.x = maxEdge.x - WIN_DEFAULT_WIDTH;

		if (this->position.y < minEdge.y)
			this->position.y = minEdge.y;
		else if (this->position.y + WIN_DEFAULT_HEIGHT > maxEdge.y)
			this->position.y = maxEdge.y - WIN_DEFAULT_HEIGHT;
	}

	UpdateView();
}

void Camera::Move(const Vector2& position)
{
	this->position += position * TIME->GetDeltaTime();

	if (bEdge)
	{
		if (this->position.x < minEdge.x)
			this->position.x = minEdge.x;
		else if (this->position.x + WIN_DEFAULT_WIDTH > maxEdge.x)
			this->position.x = maxEdge.x - WIN_DEFAULT_WIDTH;

		if (this->position.y > minEdge.y)
			this->position.y = minEdge.y;
		else if (this->position.y + WIN_DEFAULT_HEIGHT > maxEdge.y)
			this->position.y = maxEdge.y - WIN_DEFAULT_HEIGHT;
	}

	UpdateView();
}
