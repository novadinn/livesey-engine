#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

namespace Livesey {

    enum AttributeType {
	BOOL,
	INT,
	UINT,
	FLOAT,
	DOUBLE,

	BVEC2,
	BVEC3,
	BVEC4,

	IVEC2,
	IVEC3,
	IVEC4,

	UVEC2,
	UVEC3,
	UVEC4,

	VEC2,
	VEC3,
	VEC4,
	
	DVEC2,
	DVEC3,
	DVEC4,

	MAT2,
	MAT3,
	MAT4,
	MAT2X3,
	MAT3X2,
	MAT2X4,
	MAT4X2,
	MAT3X4,
	MAT4X3
    };

    struct VertexAttribute {
        VertexAttribute(AttributeType t, GLenum norm) : type_(t), norm_p_(norm) {}

	inline AttributeType getType() const { return type_; }
	inline GLenum isNormalized() const { return norm_p_; }

	size_t getSize() const {
	    switch(type_) {
	    case AttributeType::BOOL: { return 1; } break;
	    case AttributeType::INT: { return 4; } break;
	    case AttributeType::UINT: { return 4; } break;
	    case AttributeType::FLOAT: { return 4; } break;
	    case AttributeType::DOUBLE: { return 8; } break;
		
	    case AttributeType::BVEC2: { return 1; } break;
	    case AttributeType::BVEC3: { return 1; } break;
	    case AttributeType::BVEC4: { return 1; } break;
		
	    case AttributeType::IVEC2: { return 4; } break;
	    case AttributeType::IVEC3: { return 4; } break;
	    case AttributeType::IVEC4: { return 4; } break;
		
	    case AttributeType::UVEC2: { return 4; } break;
	    case AttributeType::UVEC3: { return 4; } break;
	    case AttributeType::UVEC4: { return 4; } break;
		
	    case AttributeType::VEC2: { return 4; } break;
	    case AttributeType::VEC3: { return 4; } break;
	    case AttributeType::VEC4: { return 4; } break;
		
	    case AttributeType::DVEC2: { return 8; } break;
	    case AttributeType::DVEC3: { return 8; } break;
	    case AttributeType::DVEC4: { return 8; } break;
		
	    case AttributeType::MAT2: { return 4; } break;
	    case AttributeType::MAT3: { return 4; } break;
	    case AttributeType::MAT4: { return 4; } break;
	    case AttributeType::MAT2X3: { return 4; } break;
	    case AttributeType::MAT3X2: { return 4; } break;
	    case AttributeType::MAT2X4: { return 4; } break;
	    case AttributeType::MAT4X2: { return 4; } break;
	    case AttributeType::MAT3X4: { return 4; } break;
	    case AttributeType::MAT4X3: { return 4; } break;
	    }

	    LOG_ERR("Unsupported shader type");
	    return 0;
	}

	int getCount() const {
	    switch(type_) {
	    case AttributeType::BOOL: { return 1; } break;
	    case AttributeType::INT: { return 1; } break;
	    case AttributeType::UINT: { return 1; } break;
	    case AttributeType::FLOAT: { return 1; } break;
	    case AttributeType::DOUBLE: { return 1; } break;
		
	    case AttributeType::BVEC2: { return 2; } break;
	    case AttributeType::BVEC3: { return 3; } break;
	    case AttributeType::BVEC4: { return 4; } break;
		
	    case AttributeType::IVEC2: { return 2; } break;
	    case AttributeType::IVEC3: { return 3; } break;
	    case AttributeType::IVEC4: { return 4; } break;
		
	    case AttributeType::UVEC2: { return 2; } break;
	    case AttributeType::UVEC3: { return 3; } break;
	    case AttributeType::UVEC4: { return 4; } break;
		
	    case AttributeType::VEC2: { return 2; } break;
	    case AttributeType::VEC3: { return 3; } break;
	    case AttributeType::VEC4: { return 4; } break;
		
	    case AttributeType::DVEC2: { return 2; } break;
	    case AttributeType::DVEC3: { return 3; } break;
	    case AttributeType::DVEC4: { return 4; } break;
		
	    case AttributeType::MAT2: { return 2 * 2; } break;
	    case AttributeType::MAT3: { return 3 * 3; } break;
	    case AttributeType::MAT4: { return 4 * 4; } break;
	    case AttributeType::MAT2X3: { return 2 * 3; } break;
	    case AttributeType::MAT3X2: { return 3 * 2; } break;
	    case AttributeType::MAT2X4: { return 2 * 4; } break;
	    case AttributeType::MAT4X2: { return 4 * 2; } break;
	    case AttributeType::MAT3X4: { return 3 * 4; } break;
	    case AttributeType::MAT4X3: { return 4 * 3; } break;
	    }

	    LOG_ERR("Unsupported shader type");
	    return 0;
	}
	
    private:
	AttributeType type_;
	GLenum norm_p_;
    };
}

#endif // VERTEX_ATTRIBUTE_H
