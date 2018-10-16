#include "LiarRectSprite.h"
#include <LiarPolygon.h>

namespace Liar
{
	LiarRectSprite::LiarRectSprite():
		Liar::LiarMesh()
	{
		m_geometry = Liar::LiarPolygonGeoMgr::GetGeo(Liar::LiarPolygonGeometryType::GeometryType_RectSprite);
	}


	LiarRectSprite::~LiarRectSprite()
	{
		Liar::LiarPolygonGeoMgr::ReleaseGeo(Liar::LiarPolygonGeometryType::GeometryType_RectSprite);
		m_geometry = nullptr;
	}

}