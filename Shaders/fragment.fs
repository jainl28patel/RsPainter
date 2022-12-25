#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPos;

void main()
{
    // ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specular_strength = 0.6;
    vec3 view_direction = normalize(cameraPos - FragPos);
    vec3 reflect_direction = reflect(-lightDir, norm);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0f), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
