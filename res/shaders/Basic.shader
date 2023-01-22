#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Normals;
layout(location = 2) in vec2 Text_Coor;

uniform mat4 CordinatsSystem;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat3 Normal_mat;
//uniform mat4 scale;
// 
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;



out vec2 v_TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;


void main()
{
	gl_Position = projection * view * model *vec4(position,1.0f);
	
	FragPosLightSpace = lightSpaceMatrix *model * vec4(position, 1.0f);
	v_TexCoord = Text_Coor;
	FragPos = vec3(model * vec4(position, 1.0));
	Normal = Normal_mat*Normals;
	

};



#shader fragment
#version 330 core

struct Material {
	float ambient;
	float diffuse;
	float specular;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;
	vec4 color;
	float shininess;
};
struct DirLight
{
	vec3 direction;

	vec3 ambient; //implement ambient and diffuse and all this shit
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	vec3 ambient; 
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear_;
	float quadratic;
};

struct FlashLight
{
	vec3 position;
	vec3 direction;
	float Innerangle;
	float Outerangle;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};


//don't change its name
uniform DirLight Dir_Light;
uniform Material material;
//uniform PointLight lightPoint; 
uniform FlashLight flashLight;

#define NR_POINT_LIGHTS 4
uniform PointLight lightPoint[NR_POINT_LIGHTS];

out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float far_plane;

uniform sampler2D shadowMap;
uniform samplerCube depthMap;



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 textur);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,vec3 viewDir, vec3 textur);

vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir, vec3 textur);

float ShadowCalculation(vec4 fragPosLightSpace);
float pointShadowCalculation(vec3 fragPos);


float near = 0.1;
float far = 100.0;
float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0; // back to NDC
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()							//// main ////
{


	vec3 norm = normalize(Normal);
	vec3 viewDirection = normalize(viewPos - FragPos);
	vec4 textur = texture(material.texture_diffuse1, v_TexCoord);
	vec3 result = CalcDirLight(Dir_Light, norm, viewDirection, textur.xyz);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
			result += CalcPointLight(lightPoint[i], norm, FragPos, viewDirection, textur.xyz);
	}

	result += CalcFlashLight(flashLight, norm, viewDirection, textur.xyz);


	float ratio = 1.00 / 1.52;

	

	if (material.color.w != 0)
		FragColor = vec4(result, 1) * material.color ;//
	else
		FragColor = vec4(result, textur.a) ;//
	
};

float pointShadowCalculation(vec3 fragPos)
{

	// get vector between fragment position and light position
	vec3 fragToLight = fragPos - lightPos;
	// use the light to fragment vector to sample from the depth map
	float closestDepth = texture(depthMap, fragToLight).r;
	// it is currently in linear range between [0,1].
	// re-transform back to original value
	closestDepth *= far_plane;
	// now get current linear depth as the length between the
	// fragment and light position
	float currentDepth = length(fragToLight);
	// now test for shadows

	vec3 sampleOffsetDirections[20] = vec3[]
	(
		vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
		vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
		vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
		vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
		vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
		);

	float shadow = 0.0;
	float bias = 0.15;
	int samples = 20;
	float viewDistance = length(viewPos - fragPos);
	float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;

	for (int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(depthMap, fragToLight +
			sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= far_plane; // undo mapping [0;1]
		if (currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow /= float(samples);

	if (currentDepth > far_plane)
		shadow = 0;
	return shadow;

}
vec3 CalcFlashLight(FlashLight light, vec3 normal,vec3 viewDir,vec3 textur)
{
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	float diff = max(dot(normal, lightDir), 0.0);


	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.Innerangle - light.Outerangle;
	float intensity = clamp((theta - light.Outerangle) / epsilon, 0.0, 1.0);


	
	vec3 ambient = light.ambient * textur;

	vec3 diffuse = light.diffuse * diff * textur;

	vec3 specular = light.specular * spec * texture(material.texture_specular1, v_TexCoord).xyz;

	return (ambient * material.ambient + diffuse  * intensity * material.diffuse + specular  * intensity* material.specular);
}



vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 textur)
{
	vec3 lightDir = normalize(light.position - fragPos);

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfwayDir), 0), material.shininess);
	float diff = max(dot(normal, lightDir), 0.0);

	float distance = length(light.position - fragPos);

	float denominator = (light.constant + light.linear_ * distance + light.quadratic * (distance * distance));

	float attenuation;
	if (denominator != 0)
		attenuation = (1.0 / denominator);
	else
		attenuation = 0;



	vec3 ambient = light.ambient * textur;

	vec3 diffuse = light.diffuse * diff * textur;

	vec3 specular = light.specular * spec * texture(material.texture_specular1, v_TexCoord).xyz;
	float shadow = pointShadowCalculation(FragPos);
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient * material.ambient + (1.0 - shadow)*(diffuse*material.diffuse + specular*material.specular));
}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 textur)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfwayDir), 0), material.shininess);
	float diff = max(dot(normal, lightDir), 0.0);

	float shadow = ShadowCalculation(FragPosLightSpace);

	vec3 ambient = light.ambient * textur;

	vec3 diffuse = light.diffuse * diff * textur* (1.0 - shadow);

	vec3 specular = light.specular * spec * texture(material.texture_specular1, v_TexCoord).xyz* (1.0 - shadow);

	return (ambient * material.ambient + diffuse * material.diffuse + specular * material.specular);
}

float ShadowCalculation(vec4 fragPosLightSpace)
{

	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light’s perspective (using
	// [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light’s perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow
	float bias = max(0.0018 * (1.0 - dot(Normal, Dir_Light.direction)), 0.001);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) *
				texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	//float shadow = currentDepth-bias > closestDepth ? 1.0 : 0.0;
	//if (projCoords.z > 1.0)
	//	shadow = 0.0;

	return shadow;
}