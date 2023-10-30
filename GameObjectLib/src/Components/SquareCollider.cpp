#include "Components/SquareCollider.h"

bool SquareCollider::IsColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();
	return (positionA.x < positionB.x + _colliderB.GetWidth() && positionA.x + _colliderA.GetWidth() > positionB.x && positionA.y < positionB.y + _colliderB.GetHeight() && positionA.y + _colliderA.GetHeight() > positionB.y);
}

bool SquareCollider::IsHColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();

	float leftA = positionA.x;
	float rightA = positionA.x + _colliderA.GetWidth();

	float leftB = positionB.x;
	float rightB = positionB.x + _colliderB.GetWidth();

	return (rightA > leftB) && (leftA < rightB);
}

bool SquareCollider::IsVColliding(const SquareCollider& _colliderA, const SquareCollider& _colliderB)
{
	const Maths::Vector2f positionA = _colliderA.GetOwner()->GetPosition();
	const Maths::Vector2f positionB = _colliderB.GetOwner()->GetPosition();

	float topA = positionA.y;
	float bottomA = positionA.y + _colliderA.GetHeight();

	float topB = positionB.y;
	float bottomB = positionB.y + _colliderB.GetHeight();

	return (bottomA > topB) && (topA < bottomB);
}

