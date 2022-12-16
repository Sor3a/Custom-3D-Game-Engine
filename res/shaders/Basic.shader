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
//uniform mat4 view;
//uniform mat4 projection;

//layout(std140) uniform Matrices
//{
//	mat4 projection;
//	mat4 view;
//};

out vec2 v_TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = projection * view * model *vec4(position,1.0f);
	

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

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform samplerCube skybox;



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 textur);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,vec3 viewDir, vec3 textur);

vec3 CalcFlashLight(FlashLight light, vec3 normal, vec3 viewDir, vec3 textur);


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

	vec3 R = refract(-viewDirection, norm, ratio);

	if (material.color.w != 0)
		FragColor = vec4(result, 1) * material.color * vec4(texture(skybox, R).rgb, 1.0);//
	else
		FragColor = vec4(result, textur.a) ;//
	
};

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

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient * material.ambient + diffuse*material.diffuse + specular*material.specular);
}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 textur)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(normal, halfwayDir), 0), material.shininess);
	float diff = max(dot(normal, lightDir), 0.0);

	

	vec3 ambient = light.ambient * textur;

	vec3 diffuse = light.diffuse * diff * textur;

	vec3 specular = light.specular * spec * texture(material.texture_specular1, v_TexCoord).xyz;

	return (ambient * material.ambient + diffuse * material.diffuse + specular * material.specular);
}
