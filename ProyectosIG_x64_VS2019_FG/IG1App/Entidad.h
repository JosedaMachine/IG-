#pragma once
class  Entidad {
public:
	Entidad() {};
	virtual ~Entidad() {};

	virtual void update() {};

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	virtual void setColor(glm::dvec4 mCol) = 0;

	virtual void setTexture(Texture* tex) = 0;

	// modeling matrix
	virtual glm::dmat4 const& modelMat() const = 0;
	virtual void setModelMat(glm::dmat4 const& aMat) = 0;
};
