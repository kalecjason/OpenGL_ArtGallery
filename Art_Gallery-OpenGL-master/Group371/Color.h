#ifndef COLOR
#define COLOR

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// RED HTML COLOR NAMES
#define INDIANRED glm::vec3(0.803922f,0.360784f,0.360784f)
#define LIGHTCORAL glm::vec3(0.941176f,0.501961f,0.501961f)
#define SALMON glm::vec3(0.980392f,0.501961f,0.447059f)
#define DARKSALMON glm::vec3(0.913725f,0.588235f,0.478431f)
#define LIGHTSALMON glm::vec3(1.000000f,0.627451f,0.478431f)
#define CRIMSON glm::vec3(0.862745f,0.078431f,0.235294f)
#define RED glm::vec3(1.000000f,0.000000f,0.000000f)
#define FIREBRICK glm::vec3(0.698039f,0.133333f,0.133333f)
#define DARKRED glm::vec3(0.545098f,0.000000f,0.000000f)

// PINK HTML COLOR NAMES
#define PINK glm::vec3(1.000000f,0.752941f,0.796078f)
#define LIGHTPINK glm::vec3(1.000000f,0.713726f,0.756863f)
#define HOTPINK glm::vec3(1.000000f,0.411765f,0.705882f)
#define DEEPPINK glm::vec3(1.000000f,0.078431f,0.576471f)
#define MEDIUMVIOLETRED glm::vec3(0.780392f,0.082353f,0.521569f)
#define PALEVIOLETRED glm::vec3(0.858824f,0.439216f,0.576471f)

// ORANGE HTML COLOR NAMES
#define LIGHTSALMON glm::vec3(1.000000f,0.627451f,0.478431f)
#define CORAL glm::vec3(1.000000f,0.498039f,0.313726f)
#define TOMATO glm::vec3(1.000000f,0.388235f,0.278431f)
#define ORANGERED glm::vec3(1.000000f,0.270588f,0.000000f)
#define DARKORANGE glm::vec3(1.000000f,0.549020f,0.000000f)
#define ORANGE glm::vec3(1.000000f,0.647059f,0.000000f)

// YELLOW HTML COLOR NAMES
#define GOLD glm::vec3(1.000000f,0.843137f,0.000000f)
#define YELLOW glm::vec3(1.000000f,1.000000f,0.000000f)
#define LIGHTYELLOW glm::vec3(1.000000f,1.000000f,0.878431f)
#define LEMONCHIFFON glm::vec3(1.000000f,0.980392f,0.803922f)
#define LIGHTGOLDENRODYELLOW glm::vec3(0.980392f,0.980392f,0.823529f)
#define PAPAYAWHIP glm::vec3(1.000000f,0.937255f,0.835294f)
#define MOCCASIN glm::vec3(1.000000f,0.894118f,0.709804f)
#define PEACHPUFF glm::vec3(1.000000f,0.854902f,0.725490f)
#define PALEGOLDENROD glm::vec3(0.933333f,0.909804f,0.666667f)
#define KHAKI glm::vec3(0.941176f,0.901961f,0.549020f)
#define DARKKHAKI glm::vec3(0.741176f,0.717647f,0.419608f)

// PURPLE HTML COLOR NAMES
#define LAVENDER glm::vec3(0.901961f,0.901961f,0.980392f)
#define THISTLE glm::vec3(0.847059f,0.749020f,0.847059f)
#define PLUM glm::vec3(0.866667f,0.627451f,0.866667f)
#define VIOLET glm::vec3(0.933333f,0.509804f,0.933333f)
#define ORCHID glm::vec3(0.854902f,0.439216f,0.839216f)
#define FUCHSIA glm::vec3(1.000000f,0.000000f,1.000000f)
#define MAGENTA glm::vec3(1.000000f,0.000000f,1.000000f)
#define MEDIUMORCHID glm::vec3(0.729412f,0.333333f,0.827451f)
#define MEDIUMPURPLE glm::vec3(0.576471f,0.439216f,0.858824f)
#define REBECCAPURPLE glm::vec3(0.400000f,0.200000f,0.600000f)
#define BLUEVIOLET glm::vec3(0.541176f,0.168627f,0.886275f)
#define DARKVIOLET glm::vec3(0.580392f,0.000000f,0.827451f)
#define DARKORCHID glm::vec3(0.600000f,0.196078f,0.800000f)
#define DARKMAGENTA glm::vec3(0.545098f,0.000000f,0.545098f)
#define PURPLE glm::vec3(0.501961f,0.000000f,0.501961f)
#define INDIGO glm::vec3(0.294118f,0.000000f,0.509804f)
#define SLATEBLUE glm::vec3(0.415686f,0.352941f,0.803922f)
#define DARKSLATEBLUE glm::vec3(0.282353f,0.239216f,0.545098f)
#define MEDIUMSLATEBLUE glm::vec3(0.482353f,0.407843f,0.933333f)

// GREEN HTML COLOR NAMES
#define GREENYELLOW glm::vec3(0.678431f,1.000000f,0.184314f)
#define CHARTREUSE glm::vec3(0.498039f,1.000000f,0.000000f)
#define LAWNGREEN glm::vec3(0.486275f,0.988235f,0.000000f)
#define LIME glm::vec3(0.000000f,1.000000f,0.000000f)
#define LIMEGREEN glm::vec3(0.196078f,0.803922f,0.196078f)
#define PALEGREEN glm::vec3(0.596078f,0.984314f,0.596078f)
#define LIGHTGREEN glm::vec3(0.564706f,0.933333f,0.564706f)
#define MEDIUMSPRINGGREEN glm::vec3(0.000000f,0.980392f,0.603922f)
#define SPRINGGREEN glm::vec3(0.000000f,1.000000f,0.498039f)
#define MEDIUMSEAGREEN glm::vec3(0.235294f,0.701961f,0.443137f)
#define SEAGREEN glm::vec3(0.180392f,0.545098f,0.341176f)
#define FORESTGREEN glm::vec3(0.133333f,0.545098f,0.133333f)
#define GREEN glm::vec3(0.000000f,0.501961f,0.000000f)
#define DARKGREEN glm::vec3(0.000000f,0.392157f,0.000000f)
#define YELLOWGREEN glm::vec3(0.603922f,0.803922f,0.196078f)
#define OLIVEDRAB glm::vec3(0.419608f,0.556863f,0.137255f)
#define OLIVE glm::vec3(0.501961f,0.501961f,0.000000f)
#define DARKOLIVEGREEN glm::vec3(0.333333f,0.419608f,0.184314f)
#define MEDIUMAQUAMARINE glm::vec3(0.400000f,0.803922f,0.666667f)
#define DARKSEAGREEN glm::vec3(0.560784f,0.737255f,0.545098f)
#define LIGHTSEAGREEN glm::vec3(0.125490f,0.698039f,0.666667f)
#define DARKCYAN glm::vec3(0.000000f,0.545098f,0.545098f)
#define TEAL glm::vec3(0.000000f,0.501961f,0.501961f)

// BLUE HTML COLOR NAMES
#define AQUA glm::vec3(0.000000f,1.000000f,1.000000f)
#define CYAN glm::vec3(0.000000f,1.000000f,1.000000f)
#define LIGHTCYAN glm::vec3(0.878431f,1.000000f,1.000000f)
#define PALETURQUOISE glm::vec3(0.686275f,0.933333f,0.933333f)
#define AQUAMARINE glm::vec3(0.498039f,1.000000f,0.831373f)
#define TURQUOISE glm::vec3(0.250980f,0.878431f,0.815686f)
#define MEDIUMTURQUOISE glm::vec3(0.282353f,0.819608f,0.800000f)
#define DARKTURQUOISE glm::vec3(0.000000f,0.807843f,0.819608f)
#define CADETBLUE glm::vec3(0.372549f,0.619608f,0.627451f)
#define STEELBLUE glm::vec3(0.274510f,0.509804f,0.705882f)
#define LIGHTSTEELBLUE glm::vec3(0.690196f,0.768627f,0.870588f)
#define POWDERBLUE glm::vec3(0.690196f,0.878431f,0.901961f)
#define LIGHTBLUE glm::vec3(0.678431f,0.847059f,0.901961f)
#define SKYBLUE glm::vec3(0.529412f,0.807843f,0.921569f)
#define LIGHTSKYBLUE glm::vec3(0.529412f,0.807843f,0.980392f)
#define DEEPSKYBLUE glm::vec3(0.000000f,0.749020f,1.000000f)
#define DODGERBLUE glm::vec3(0.117647f,0.564706f,1.000000f)
#define CORNFLOWERBLUE glm::vec3(0.392157f,0.584314f,0.929412f)
#define MEDIUMSLATEBLUE glm::vec3(0.482353f,0.407843f,0.933333f)
#define ROYALBLUE glm::vec3(0.254902f,0.411765f,0.882353f)
#define BLUE glm::vec3(0.000000f,0.000000f,1.000000f)
#define MEDIUMBLUE glm::vec3(0.000000f,0.000000f,0.803922f)
#define DARKBLUE glm::vec3(0.000000f,0.000000f,0.545098f)
#define NAVY glm::vec3(0.000000f,0.000000f,0.501961f)
#define MIDNIGHTBLUE glm::vec3(0.098039f,0.098039f,0.439216f)

// BROWN HTML COLOR NAMES
#define CORNSILK glm::vec3(1.000000f,0.972549f,0.862745f)
#define BLANCHEDALMOND glm::vec3(1.000000f,0.921569f,0.803922f)
#define BISQUE glm::vec3(1.000000f,0.894118f,0.768627f)
#define NAVAJOWHITE glm::vec3(1.000000f,0.870588f,0.678431f)
#define WHEAT glm::vec3(0.960784f,0.870588f,0.701961f)
#define BURLYWOOD glm::vec3(0.870588f,0.721569f,0.529412f)
#define TAN glm::vec3(0.823529f,0.705882f,0.549020f)
#define ROSYBROWN glm::vec3(0.737255f,0.560784f,0.560784f)
#define SANDYBROWN glm::vec3(0.956863f,0.643137f,0.376471f)
#define GOLDENROD glm::vec3(0.854902f,0.647059f,0.125490f)
#define DARKGOLDENROD glm::vec3(0.721569f,0.525490f,0.043137f)
#define PERU glm::vec3(0.803922f,0.521569f,0.247059f)
#define CHOCOLATE glm::vec3(0.823529f,0.411765f,0.117647f)
#define SADDLEBROWN glm::vec3(0.545098f,0.270588f,0.074510f)
#define SIENNA glm::vec3(0.627451f,0.321569f,0.176471f)
#define BROWN glm::vec3(0.647059f,0.164706f,0.164706f)
#define MAROON glm::vec3(0.501961f,0.000000f,0.000000f)

// WHITE HTML COLOR NAMES
#define WHITE glm::vec3(1.000000f,1.000000f,1.000000f)
#define SNOW glm::vec3(1.000000f,0.980392f,0.980392f)
#define HONEYDEW glm::vec3(0.941176f,1.000000f,0.941176f)
#define MINTCREAM glm::vec3(0.960784f,1.000000f,0.980392f)
#define AZURE glm::vec3(0.941176f,1.000000f,1.000000f)
#define ALICEBLUE glm::vec3(0.941176f,0.972549f,1.000000f)
#define GHOSTWHITE glm::vec3(0.972549f,0.972549f,1.000000f)
#define WHITESMOKE glm::vec3(0.960784f,0.960784f,0.960784f)
#define SEASHELL glm::vec3(1.000000f,0.960784f,0.933333f)
#define BEIGE glm::vec3(0.960784f,0.960784f,0.862745f)
#define OLDLACE glm::vec3(0.992157f,0.960784f,0.901961f)
#define FLORALWHITE glm::vec3(1.000000f,0.980392f,0.941176f)
#define IVORY glm::vec3(1.000000f,1.000000f,0.941176f)
#define ANTIQUEWHITE glm::vec3(0.980392f,0.921569f,0.843137f)
#define LINEN glm::vec3(0.980392f,0.941176f,0.901961f)
#define LAVENDERBLUSH glm::vec3(1.000000f,0.941176f,0.960784f)
#define MISTYROSE glm::vec3(1.000000f,0.894118f,0.882353f)

// GRAY HTML COLOR NAMES
#define GAINSBORO glm::vec3(0.862745f,0.862745f,0.862745f)
#define LIGHTGRAY glm::vec3(0.827451f,0.827451f,0.827451f)
#define SILVER glm::vec3(0.752941f,0.752941f,0.752941f)
#define DARKGRAY glm::vec3(0.662745f,0.662745f,0.662745f)
#define GRAY glm::vec3(0.501961f,0.501961f,0.501961f)
#define DIMGRAY glm::vec3(0.411765f,0.411765f,0.411765f)
#define LIGHTSLATEGRAY glm::vec3(0.466667f,0.533333f,0.600000f)
#define SLATEGRAY glm::vec3(0.439216f,0.501961f,0.564706f)
#define DARKSLATEGRAY glm::vec3(0.184314f,0.309804f,0.309804f)
#define BLACK glm::vec3(0.000000f,0.000000f,0.000000f)


// Materials

#define MATERIAL_EMERALD		Material {glm::vec3(0.0215	,0.1745	,0.0215	), glm::vec3(0.07568,0.61424	,0.07568	), glm::vec3(0.633		,0.727811	,0.633		),0.6f		* 128};
#define MATERIAL_JADE			Material {glm::vec3(0.135	,0.2225	,0.1575	), glm::vec3(0.54	,0.89		,0.63		), glm::vec3(0.316228	,0.316228	,0.316228	),0.1f		* 128};
#define MATERIAL_OBSIDIAN		Material {glm::vec3(0.05375	,0.05	,0.06625), glm::vec3(0.18275,0.17		,0.22525	), glm::vec3(0.332741	,0.328634	,0.346435	),0.3f		* 128};
#define MATERIAL_PEARL			Material {glm::vec3(0.25	,0.20725,0.20725), glm::vec3(1		,0.829		,0.829		), glm::vec3(0.296648	,0.296648	,0.296648	),0.088f	* 128};
#define MATERIAL_RUBY			Material {glm::vec3(0.1745	,0.01175,0.01175), glm::vec3(0.61424,0.04136	,0.04136	), glm::vec3(0.727811	,0.626959	,0.626959	),0.6f		* 128};
#define MATERIAL_TURQUOISE		Material {glm::vec3(0.1		,0.18725,0.1745 ), glm::vec3(0.396	,0.74151	,0.69102	), glm::vec3(0.297254	,0.30829	,0.306678	),0.1f		* 128};
#define MATERIAL_BRASS			Material {glm::vec3(0.32941 ,0.22352,0.02745), glm::vec3(0.780392,0.568627	,0.113725	), glm::vec3(0.992157	,0.941176	,0.807843	),0.2179f	* 128};
#define MATERIAL_BRONZE			Material {glm::vec3(0.2125	,0.1275	,0.054	), glm::vec3(0.714	,0.4284		,0.18144	), glm::vec3(0.393548	,0.271906	,0.166721	),0.2f		* 128};
#define MATERIAL_CHROME			Material {glm::vec3(0.25	,0.25	,0.25	), glm::vec3(0.4	,0.4		,0.4		), glm::vec3(0.774597	,0.774597	,0.774597	),0.6f		* 128};
#define MATERIAL_COPPER			Material {glm::vec3(0.19125	,0.0735	,0.0225	), glm::vec3(0.7038	,0.27048	,0.0828		), glm::vec3(0.256777	,0.137622	,0.086014	),0.1f		* 128};
#define MATERIAL_GOLD			Material {glm::vec3(0.24725	,0.1995	,0.0745	), glm::vec3(0.75164,0.60648	,0.22648	), glm::vec3(0.628281	,0.555802	,0.366065	),0.4f		* 128};
#define MATERIAL_SILVER			Material {glm::vec3(0.19225	,0.19225,0.19225), glm::vec3(0.50754,0.50754	,0.50754	), glm::vec3(0.508273	,0.508273	,0.508273	),0.4f		* 128};
#define MATERIAL_BLACK_PLASTIC	Material {glm::vec3(0.0		,0.0	,0.0	), glm::vec3(0.01	,0.01		,0.01		), glm::vec3(0.50		,0.50		,0.50		),0.25f		* 128};
#define MATERIAL_CYAN_PLASTIC	Material {glm::vec3(0.0		,0.1	,0.06   ), glm::vec3(0.0	,0.50980392	,0.50980392	), glm::vec3(0.50196078	,0.50196078	,0.50196078	),0.25f		* 128};
#define MATERIAL_GREEN_PLASTIC	Material {glm::vec3(0.0		,0.0	,0.0	), glm::vec3(0.1	,0.35		,0.1		), glm::vec3(0.45		,0.55		,0.45		),0.25f		* 128};
#define MATERIAL_RED_PLASTIC	Material {glm::vec3(0.0		,0.0	,0.0	), glm::vec3(0.5	,0.0		,0.0		), glm::vec3(0.7		,0.6		,0.6		),0.25f		* 128};
#define MATERIAL_WHITE_PLASTIC	Material {glm::vec3(0.0		,0.0	,0.0	), glm::vec3(0.55	,0.55		,0.55		), glm::vec3(0.70		,0.70		,0.70		),0.25f		* 128};
#define MATERIAL_YELLOW_PLASTIC	Material {glm::vec3(0.0		,0.0	,0.0	), glm::vec3(0.5	,0.5		,0.0		), glm::vec3(0.60		,0.60		,0.50		),0.25f		* 128};
#define MATERIAL_BLACK_RUBBER	Material {glm::vec3(0.02	,0.02	,0.02	), glm::vec3(0.01	,0.01		,0.01		), glm::vec3(0.4		,0.4		,0.4		),0.078125f * 128};
#define MATERIAL_CYAN_RUBBER	Material {glm::vec3(0.0		,0.05	,0.05	), glm::vec3(0.4	,0.5		,0.5		), glm::vec3(0.04		,0.7		,0.7		),0.078125f * 128};
#define MATERIAL_GREEN_RUBBER	Material {glm::vec3(0.0		,0.05	,0.0	), glm::vec3(0.4	,0.5		,0.4		), glm::vec3(0.04		,0.7		,0.04		),0.078125f * 128};
#define MATERIAL_RED_RUBBER		Material {glm::vec3(0.05	,0.0	,0.0	), glm::vec3(0.5	,0.4		,0.4		), glm::vec3(0.7		,0.04		,0.04		),0.078125f * 128};
#define MATERIAL_WHITE_RUBBER	Material {glm::vec3(0.05	,0.05	,0.05	), glm::vec3(0.5	,0.5		,0.5		), glm::vec3(0.7		,0.7		,0.7		),0.078125f * 128};
#define MATERIAL_YELLOW_RUBBER	Material {glm::vec3(0.05	,0.05	,0.0	), glm::vec3(0.5	,0.5		,0.4		), glm::vec3(0.7		,0.7		,0.04		),0.078125f * 128};




static Material randomMaterial() {
	float newRed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
	float newGreen = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
	float newBlue = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));

	Material m;
	m.ambient = glm::vec3(newRed, newGreen, newBlue);
	m.diffuse= glm::vec3(newRed, newGreen, newBlue);
	m.specular = glm::vec3(1, 1, 1);
	m.shininess = 128;
	return m;
}


#endif // !COLOR
