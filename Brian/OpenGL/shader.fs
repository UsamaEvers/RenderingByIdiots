
#version 330 core

uniform vec3 uEyePosition;
uniform vec3 uColor;
uniform vec3 uCool;
uniform vec3 uWarm;

in vec2 vUv;
in vec3 vNormal;
in vec3 vPos;

out vec4 FragColor;

#define lightPos (vec3(5., 20., 0.))

vec3 cCool()
{
    return uCool+vec3(vUv, 0.)*.25;
}
vec3 cWarm()
{
    return uWarm+vec3(vUv, 0.)*.25;
}

vec3 unlit()
{
    return cCool()*.5;
}

vec3 lit(vec3 l, vec3 n, vec3 v)
{
    vec3 r_l = reflect(-l, n);
    float s = clamp(100.*(dot(r_l, v))-97., 0., 1.);
    vec3 hightLightColor = vec3(2., 2., 2.);
    return mix(cWarm(), hightLightColor, s);
}

void main()
{
    vec3 n = normalize(vNormal);
    vec3 v = normalize(uEyePosition.xyz-vPos);

    vec4 color = vec4(cCool(), 1.);

    vec3 l = normalize(lightPos-vPos);
    float NdL = clamp(dot(n, l), 0., 1.);
    color.rgb += NdL * lit(l, n, v);

    FragColor = color;
} 