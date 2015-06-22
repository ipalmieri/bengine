#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>

#include <tools.h>
#include <beng.h>
#include <GL/freeglut.h>

using namespace std;
using namespace tools;
using namespace engine;

renderer *rend;


engnode *red_cube;
engnode *blue_cube;
engnode *white_cube;
engnode *green_cube;
engnode *tex_cube;
engnode *plan1;
engnode *bol1;

engnode *gt[11];

void init()
{
   rend = rendererSingleton::getInstance();

   light *l1 = rend->createLight(Vector4(10.0f, 10.0f, 5.0f, 1.0f));   
   light *l2 = rend->createLight(Vector4(-10.0f, -10.0f, 5.0f, 1.0f));
   light *l3 = rend->createLight(Vector4(-10.0f, 10.0f, 5.0f, 1.0f));
   light *l4 = rend->createLight(Vector4(10.0f, -10.0f, 5.0f, 1.0f));
   light *l5 = rend->createLight(Vector4(0.0f, 0.0f, 20.0f, 1.0f));

   l1->kq = l2->kq = l3->kq = l4->kq = l5->kq = 0.013;

   vector<shader *> dshaders;
   dshaders.push_back(rend->createVertexShader(DEF_VSHADER));
   dshaders.push_back(rend->createFragmentShader(DEF_FSHADER));
   
   program *dprog = rend->createProgram(dshaders);
   
 
   //create scene
   material *mwhite = rend->createMaterial();
   material *mred = rend->createMaterial();
   material *mblue = rend->createMaterial();
   material *mgreen = rend->createMaterial();
   material *mtex = rend->createMaterial();
   material *mplan = rend->createMaterial();
   material *mbol = rend->createMaterial();


   mwhite->diffuseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
   mred->diffuseColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
   mblue->diffuseColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
   mgreen->diffuseColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
   mtex->diffuseColor = Vector4(0.0f, 1.0f, 1.0f, 1.0f);
   mtex->diffuseMap = rend->createTexture("memory-1948.jpg");
   mtex->specularColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
   mplan->diffuseColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
   mbol->diffuseColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
   mbol->specularColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
   mbol->diffuseMap = rend->createTexture("venus-1.jpg");

   mesh *meshe = rend->createMesh();
   createCubeMesh(meshe, 1.0f);
   
   mesh *plan_mesh = rend->createMesh();
   createPlaneMesh(plan_mesh, 50, 50);

   mesh *bol_mesh = rend->createMesh();
   createSphereMesh(bol_mesh, 1.0f, 100, 100);

   
   red_cube = new engnode(rend->rootNode());
   blue_cube = new engnode(rend->rootNode());
   white_cube = new engnode(rend->rootNode());
   green_cube = new engnode(rend->rootNode());
   tex_cube = new engnode(rend->rootNode());
   plan1 = new engnode(rend->rootNode());
   bol1 = new engnode(rend->rootNode());

   red_cube->matrix.setPosition(Vector3(2.0f, 0.0f, 0.0f));
   blue_cube->matrix.setPosition(Vector3(0.0f, 0.0f, 2.0f));
   white_cube->matrix.setPosition(Vector3(0.0f, 0.0f, 0.0f));
   green_cube->matrix.setPosition(Vector3(0.0f, 2.0f, 0.0f));
   tex_cube->matrix.setPosition(Vector3(0.0f, 0.0f, 4.0f));
   plan1->matrix.setPosition(Vector3(0.0f, 0.0f, -0.5f));
   bol1->matrix.setPosition(Vector3(3.0f, 3.0f, 3.0f));

   red_cube->addEngset(meshe, mred, dprog);
   blue_cube->addEngset(meshe, mblue, dprog);
   white_cube->addEngset(meshe, mwhite, dprog);
   green_cube->addEngset(meshe, mgreen, dprog);
   tex_cube->addEngset(meshe, mtex, dprog);
   plan1->addEngset(plan_mesh, mplan, dprog);
   bol1->addEngset(bol_mesh, mbol, dprog);



  for (unsigned i = 0; i < 11; i++)
   {
      material *mt = rend->createMaterial();
      
      float cor = (float) i / (float) 11;

      mt->diffuseColor = Vector4(cor, cor, cor, 1.0f);
      
      gt[i] = new engnode(rend->rootNode());

      gt[i]->matrix.setPosition(Vector3(-10, (float) i - 5, 10));

      gt[i]->addEngset(meshe, mt, dprog);
      
   }
  


}

void keyboard(unsigned char key, int x, int y)
{
   camera *cam = rend->activeCamera();

   double step = 0.2;

   switch (key)
   {
      case 27: rendererSingleton::stopInstance(); exit(EXIT_SUCCESS); break;

      case 'w': cam->moveForward(step); break;
      case 's': cam->moveForward(-step); break;
      case 'd': cam->moveRight(step); break;
      case 'a': cam->moveRight(-step); break;
      case 'q': cam->moveUpward(step); break;
      case 'e': cam->moveUpward(-step); break;

   }
}

void specialKeyboard(int key, int x, int y)
{
   camera *cam = rend->activeCamera();

   double step = 0.02;

   switch (key)
   {  
      case GLUT_KEY_UP: cam->addPitch(step); break;
      case GLUT_KEY_DOWN: cam->addPitch(-step); break;
      case GLUT_KEY_RIGHT: cam->addYaw(step); break;
      case GLUT_KEY_LEFT: cam->addYaw(-step); break;
      case GLUT_KEY_PAGE_UP: cam->addRoll(step); break;
      case GLUT_KEY_PAGE_DOWN: cam->addRoll(-step); break;
  }
}

void reshape(int w, int h)
{
   rend->resetScreen(0, 0, w, h);
}

void display()
{
   timeval t1, t2;
   static double dt = 0.0;
   static unsigned fcount = 0;
   static double dt_acc = 0.0;

   gettimeofday(&t1, NULL);


   // scene animation
   tex_cube->matrix = tex_cube->matrix * transMatrix::rotationMatrix(Vector3(0, 0, 1), dt);

   static float w = 0;
   float r = 10.0f;
   w = w + dt;

   bol1->matrix.setPosition(Vector3(r*cos(w), r*sin(w), 3));

   bol1->matrix = bol1->matrix * transMatrix::rotationMatrix(Vector3(0, 0, 1), dt*3);

   //---    

   

   rend->drawScene();

   fcount++;

   bCheckError();


   glutSwapBuffers();
   glutPostRedisplay();

   
   
   
   gettimeofday(&t2, NULL);

   dt = (t2.tv_sec - t1.tv_sec)* 1000.0;      // sec to ms
   dt += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
   dt /= 1000;

   dt_acc = dt_acc + dt;

   if (dt_acc > 2.0f)
   {

      //cout << dt << " ms.\n";
      
      cout << "\rFPS: " << ((double) fcount) / dt_acc << " " << endl;

      fcount = 0;
      dt_acc = 0.0;
   }
}

void _main(int argc, char **argv)
{

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(100, 100);

   //glutInitContextVersion(4, 2);
   //glutInitContextProfile(GLUT_CORE_PROFILE);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
   
   glutCreateWindow("bengine");


   //glewExperimental = GL_TRUE; 
   if (glewInit() != GLEW_OK)
      throw runtime_error("glewInit failed");
   glGetError();


   
   cout << "Bengine beta loading..." << endl;
   cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
   cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
   cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
   cout << "Renderer: " << glGetString(GL_RENDERER) << endl;


   init();
   
   glutDisplayFunc(display);
   // glutIdleFunc(idlef);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeyboard);
   //glutPassiveMotionFunc(mousePassive);


   glutMainLoop();

}


int main(int argc, char **argv)
{
   try {

      logger::startLog("data/logs/logmain", "beng");

      _main(argc, argv);

   } catch (const exception &e){

      std::cerr << "ERROR: " << e.what() << std::endl;

      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}


