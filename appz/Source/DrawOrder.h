#pragma once
#include "Mesh.h"
#include "MatrixStack.h"
#include "Custom Functions.h"
#include "Voxel.h"
#include "Force.h"

class Graphics;

struct Rotation
{
	float x;
	float y;
	float z;
	void Set(const float rotX, const float rotY, const float rotZ)
	{
		x = rotX;
		y = rotY;
		z = rotZ;
	}

	Mtx44 MatrixX() const
	{
		Mtx44 matrixX;

		matrixX.SetToRotation(x,1.0f,0.0f,0.0f);

		return matrixX;
	}

	Mtx44 MatrixY() const
	{
		Mtx44 matrixY;

		matrixY.SetToRotation(y,0.0f,1.0f,0.0f);

		return matrixY;
	}

	Mtx44 MatrixZ() const
	{
		Mtx44 matrixZ;

		matrixZ.SetToRotation(z,0.0f,0.0f,1.0f);

		return matrixZ;
	}

	Rotation(const float rotX = 0, const float rotY = 0, const float rotZ = 0)
	{
		Set(rotX, rotY, rotZ);
	}

	void operator=(Rotation rotate)
	{
		x = rotate.x;
		y = rotate.y;
		z = rotate.z;
	}

	void operator+=(Rotation rotate)
	{
		x += rotate.x;
		y += rotate.y;
		z += rotate.z;
	}

	void operator+(Rotation rotate)
	{
		Rotation newRotate;

		newRotate = *this;
		newRotate += rotate;
	}
};

struct Transformation
{
	Vector3 translate;
	Rotation rotate;
	Vector3 scale;
	Vector3 pivot;

	Transformation()
	{
		scale.Set(1,1,1);
	}

	Mtx44 Matrix() const
	{
		Mtx44 translation, rotation, scalation, reorientate;
		translation.SetToTranslation(translate);
		reorientate.SetToTranslation(pivot);
		scalation.SetToScale(scale.x,scale.y,scale.z);
		rotation = reorientate.GetInverse() * rotate.MatrixX() * rotate.MatrixY() * rotate.MatrixZ() * reorientate;

		return translation * rotation * scalation;
	}
};

class drawOrder
{
public:
	drawOrder();
	~drawOrder();
	Vector3 GetAcceleration();
	Vector3 GetMomentum();
	Mtx44 GetMatrix() const;
	Mesh* GetMesh();
	Material GetMaterial();
	unsigned GetDrawMode();
	float GetMaxX() const;
	float GetMinX() const;
	float GetMaxY() const;
	float GetMinY() const;
	float GetMaxZ() const;
	float GetMinZ() const;
	float GetMass() const;
	float GetKinetic();
	bool IsLightEnabled();
	bool IsCollidingWith(drawOrder& draw) const;
	void SetTerminalVelocityTo(Vector3 vector);
	void SetMaterial(const Material& mat);
	void SetVelocityTo(Vector3 newVelocity);
	void SetMomentumTo(Vector3 momentum);
	void SetParentAs(drawOrder* parent);
	void CapVelocityToTerminal();
	void AddForce(Vector3 force);
	void AddForce(Force force);
	void ApplyFriction();
	void SetVoxelsToWorldPosition();
	void SetVoxelsToOrgin();
	void UpdateForcesTo(const double deltaTime);
	void UpdateVelocity(const double deltaTime);
	void UpdateTo(const double deltaTime);
	void GainMomentumFrom(drawOrder* draw, Vector3 momentumGain);
	void LoseMomentumTo(drawOrder* draw, Vector3 momentumLost);
	void Execute(Graphics& gfx);
	void Render() const;
	void GenerateVoxels();
	void RenderPartial(const unsigned offset, const unsigned count) const;
private:
	Mtx44 GetModelTransform() const;
public:
	Mesh* geometry;
	Material material;
	unsigned drawMode;
	bool enableLight;
	float mass;
	float bounce;
	float staticFriction;
	float kineticFriction;
	unsigned boundRadius;
	Transformation transform;
	//this transformation will only apply to the parent and not it's children
	Transformation selfTransform;
	drawOrder* parent;
	std::vector<drawOrder*> children;
	std::vector<Voxel> voxels;
	std::vector<Force> forces;
	Vector3 velocity;
	Vector3 terminalVelocity;
};