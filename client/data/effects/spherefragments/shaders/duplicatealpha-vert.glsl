varying vec2 uv;


void main()
{	
   uv = gl_MultiTexCoord0.xy;

   gl_Position = gl_Vertex;
}
