#include "stdafx.h"
#include "Collision.h"

Collision::RECT::RECT(const Vector2& position, const Vector2& scale)
{
	min = position - scale * 0.5f;
	max = position + scale * 0.5f;
}

Collision::CIRCLE::CIRCLE(const Vector2& position, const Vector2& scale)
{
	pivot = position;
	radius = scale.x * 0.5f;
}

bool Collision::IntersectRectCoord(const RECT& rect, const Vector2& coord)
{
	if (rect.min.x < coord.x && coord.x < rect.max.x &&
		rect.min.y < coord.y && coord.y < rect.max.y)
		return true;
	return false;
}

bool Collision::IntersectCircleCoord(const CIRCLE& circle, const Vector2& coord)
{
	Vector2 distance = coord - circle.pivot;
	if (distance.Length() < circle.radius)
		return true;
	return false;
}

bool Collision::IntersectRectRect(const RECT& rect1, const RECT& rect2)
{
	if (rect1.min.x <= rect2.max.x && rect1.max.x >= rect2.min.x &&
		rect1.min.y <= rect2.max.y && rect1.max.y >= rect2.min.y)
		return true;
	return false;
}

bool Collision::IntersectRectRect(const Object& object1, const Object& object2)
{
	Vector2 distance = object2.GetPosition() - object1.GetPosition();
	Vector2 rect1Up = object1.GetUpVector() * object1.GetScale().y * 0.5f;
	Vector2 rect1Right = object1.GetRightVector() * object1.GetScale().x * 0.5f;
	Vector2 rect2Up = object2.GetUpVector() * object2.GetScale().y * 0.5f;
	Vector2 rect2Right = object2.GetRightVector() * object2.GetScale().x * 0.5f;

	float a, b, c;

	c = fabs(distance.Dot(object1.GetRightVector()));
	b = object1.GetScale().x * 0.5f;
	a = fabs(rect2Up.Dot(object1.GetRightVector())) + fabs(rect2Right.Dot(object1.GetRightVector()));
	if (c > a + b) return false;

	c = fabs(distance.Dot(object1.GetUpVector()));
	b = object1.GetScale().y * 0.5f;
	a = fabs(rect2Up.Dot(object1.GetUpVector())) + fabs(rect2Right.Dot(object1.GetUpVector()));
	if (c > a + b) return false;

	c = fabs(distance.Dot(object2.GetRightVector()));
	b = object2.GetScale().x * 0.5f;
	a = fabs(rect1Up.Dot(object2.GetRightVector())) + fabs(rect1Right.Dot(object2.GetRightVector()));
	if (c > a + b) return false;

	c = fabs(distance.Dot(object2.GetUpVector()));
	b = object2.GetScale().y * 0.5f;
	a = fabs(rect1Up.Dot(object2.GetUpVector())) + fabs(rect1Right.Dot(object2.GetUpVector()));
	if (c > a + b) return false;

	return true;
}

bool Collision::IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2)
{
	Vector2 distance = circle2.pivot - circle1.pivot;
	if (distance.Length() < circle1.radius + circle2.radius)
		return true;
	return false;
}

bool Collision::IntersectRectCircle(const RECT& rect, const CIRCLE& circle)
{
	Vector2 rectPivot = (rect.max + rect.min) * 0.5f;
	Vector2 rectScale = rect.max - rect.min;

	RECT wRect(rectPivot, rectScale + Vector2(circle.radius * 2.0f, 0.0f));
	if (IntersectRectCoord(wRect, circle.pivot))
		return true;

	RECT hRect(rectPivot, rectScale + Vector2(0.0f, circle.radius * 2.0f));
	if (IntersectRectCoord(hRect, circle.pivot))
		return true;

	array<Vector2, 4> edges;
	edges[0] = rect.min;
	edges[1] = rect.max;
	edges[2] = Vector2(rect.min.x, rect.max.y);
	edges[3] = Vector2(rect.max.x, rect.min.y);
	for (const auto& edge : edges)
		if (IntersectCircleCoord(circle, edge))
			return true;

	return false;
}
