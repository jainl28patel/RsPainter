#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    // Cosntants
    float constant;
    float linear;
    float quadratic;

    vec3 direction;
    vec3 position;
    float cuttoff;
    float outerCuttoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform Material material;
uniform Light light;
uniform vec3 cameraPos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

    // specular
    vec3 view_direction = normalize(cameraPos - FragPos);
    vec3 reflect_direction = reflect(-lightDir, norm);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;

    // SpotLight with Soft Edges
    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cuttoff - light.outerCuttoff;
    float intensity = clamp((theta - light.outerCuttoff) / epsilon, 0.0, 1.0);
    specular *= intensity;
    diffuse *= intensity;

    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
