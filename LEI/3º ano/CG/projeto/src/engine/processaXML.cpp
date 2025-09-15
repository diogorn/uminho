
#include "engine/World.h"
#include "tinyxml/tinyxml.h"
#include "ficheiro3d/Ficheiro.h"
#include "figuras/Triangles.h"
#include <map>
#include <utility>

void processaXML_janela(FILE* f,World& w,TiXmlElement* janela) {

    //Janela não existe
    if (janela == nullptr) {
        fprintf(f,"[JANELA] Não existe...\n");
        return;
    }

    //Obter width
    const char* width = janela->Attribute("width");

        //Width não existe
        if (width == nullptr) {
            fprintf(f,"[JANELA::width] Não existe\n");
        }
        else {
            w.width = atoi(width);
            fprintf(f,"[JANELA::width] Definido! (%d)\n",w.width);
        }


    //Obter height
    const char* height = janela->Attribute("height");

        //Height não existe
        if (height == nullptr) {
            fprintf(f,"[JANELA::height] Não existe\n");
        }
        else {
            w.height = atoi(height);
            fprintf(f,"[JANELA::height] Definido! (%d)\n",w.height);
        }

}

void processaXML_camera(FILE* f,World& w,TiXmlElement* camera) {

    //Camera não existe
    if (camera == nullptr) {
        fprintf(f,"[CAMERA] Não existe...\n");
        return;
    }

    //Obter position
    TiXmlElement* position = camera->FirstChildElement("position");

        //Verifica se posição existe
        if (position != nullptr) {

            //Obter posição x
            const char* position_x = position->Attribute("x");

            //Posição x não existe
            if (position_x == nullptr) {
                fprintf(f,"[CAMERA::position::x] Não existe\n");
            }
            else {
                w.pos_x = atof(position_x);
                fprintf(f,"[CAMERA::position::x] Definido! (%f)\n",w.pos_x);
            }

            //Obter posição y
            const char* position_y = position->Attribute("y");

            //Posição y não existe
            if (position_y == nullptr) {
                fprintf(f,"[CAMERA::position::y] Não existe\n");
            }
            else {
                w.pos_y = atof(position_y);
                fprintf(f,"[CAMERA::position::y] Definido! (%f)\n",w.pos_y);
            }

            //Obter posição z
            const char* position_z = position->Attribute("z");

            //Posição z não existe
            if (position_z == nullptr) {
                fprintf(f,"[CAMERA::position::z] Não existe\n");
            }
            else {
                w.pos_z = atof(position_z);
                fprintf(f,"[CAMERA::position::z] Definido! (%f)\n",w.pos_z);
            }

        }
        //Posição não existe
        else {
            fprintf(f,"[CAMERA::position] Não existe...\n");
        }

    //Obter lookAt
    TiXmlElement* lookAt = camera->FirstChildElement("lookAt");

        //Verifica se lookAt existe
        if (lookAt != nullptr) {

            //Obter camera x
            const char* camera_x = lookAt->Attribute("x");

            //camera x não existe
            if (camera_x == nullptr) {
                fprintf(f,"[CAMERA::lookAt::x] Não existe\n");
            }
            else {
                w.camera_x = atof(camera_x);
                fprintf(f,"[CAMERA::lookAt::x] Definido! (%f)\n",w.camera_x);
            }

            //Obter camera y
            const char* camera_y = lookAt->Attribute("y");

            //camera y não existe
            if (camera_y == nullptr) {
                fprintf(f,"[CAMERA::lookAt::y] Não existe\n");
            }
            else {
                w.camera_y = atof(camera_y);
                fprintf(f,"[CAMERA::lookAt::y] Definido! (%f)\n",w.camera_y);
            }

            //Obter camera z
            const char* camera_z = lookAt->Attribute("z");

            //camera z não existe
            if (camera_z == nullptr) {
                fprintf(f,"[CAMERA::lookAt::z] Não existe\n");
            }
            else {
                w.camera_z = atof(camera_z);
                fprintf(f,"[CAMERA::lookAt::z] Definido! (%f)\n",w.camera_z);
            }

        }
        //lookAt não existe
        else {
            fprintf(f,"[CAMERA::lookAt] Não existe...\n");
        }

    //Obter up
    TiXmlElement* up = camera->FirstChildElement("up");

        //Verifica se vetor normal existe
        if (up != nullptr) {

            //Obter vetor normal x
            const char* up_x = up->Attribute("x");

            //Vetor normal x não existe
            if (up_x == nullptr) {
                fprintf(f,"[CAMERA::up::x] Não existe\n");
            }
            else {
                w.normal_x = atof(up_x);
                fprintf(f,"[CAMERA::up::x] Definido! (%f)\n",w.normal_x);
            }

            //Obter vetor normal y
            const char* up_y = up->Attribute("y");

            //Vetor normal y não existe
            if (up_y == nullptr) {
                fprintf(f,"[CAMERA::up::y] Não existe\n");
            }
            else {
                w.normal_y = atof(up_y);
                fprintf(f,"[CAMERA::up::y] Definido! (%f)\n",w.normal_y);
            }

            //Obter vetor normal z
            const char* up_z = up->Attribute("z");

            //Vetor normal z não existe
            if (up_z == nullptr) {
                fprintf(f,"[CAMERA::up::z] Não existe\n");
            }
            else {
                w.normal_z = atof(up_z);
                fprintf(f,"[CAMERA::up::z] Definido! (%f)\n",w.normal_z);
            }

        }
        //Vetor normal não existe
        else {
            fprintf(f,"[CAMERA::up] Não existe...\n");
        }

    //Obter projection
    TiXmlElement* projection = camera->FirstChildElement("projection");

        //Verifica se projeção existe
        if (projection != nullptr) {

            //Obter fov
            const char* fov = projection->Attribute("fov");

            //Fov não existe
            if (fov == nullptr) {
                fprintf(f,"[CAMERA::projection::fov] Não existe\n");
            }
            else {
                w.fov = atof(fov);
                fprintf(f,"[CAMERA::projection::fov] Definido! (%f)\n",w.fov);
            }

            //Obter near
            const char* near = projection->Attribute("near");

            //Near não existe
            if (near == nullptr) {
                fprintf(f,"[CAMERA::projection::near] Não existe\n");
            }
            else {
                w.near = atof(near);
                fprintf(f,"[CAMERA::projection::near] Definido! (%f)\n",w.near);
            }

            //Obter far
            const char* far = projection->Attribute("far");

            //Far não existe
            if (far == nullptr) {
                fprintf(f,"[CAMERA::projection::far] Não existe\n");
            }
            else {
                w.far = atof(far);
                fprintf(f,"[CAMERA::projection::far] Definido! (%f)\n",w.far);
            }

        }
        //Projeção não existe
        else {
            fprintf(f,"[CAMERA::projection] Não existe...\n");
        }

        //<free disable="True" sensitivity="1.0" noNeedClick="True" limitedAngle="False" />
    //Obter Camera livre
    TiXmlElement* free = camera->FirstChildElement("free");

        //Verifica se camera livre existe
        if (free != nullptr) {

            //Obter disable
            const char* disable = free->Attribute("disable");

            //Disable não existe
            if (disable == nullptr) {
                fprintf(f,"[CAMERA::free::disable] Não existe\n");
            }
            else {

                if (strcasecmp("True",disable) == 0)
                    w.free_disable = true;

                fprintf(f,"[CAMERA::free::disable] Definido! (%d)\n",w.free_disable);

            }

            //Obter Sensitivity
            const char* sensitivity = free->Attribute("sensitivity");

            //Sensitivity não existe
            if (sensitivity == nullptr) {
                fprintf(f,"[CAMERA::free::sensitivity] Não existe\n");
            }
            else {
                w.sensitivity = atof(sensitivity);
                fprintf(f,"[CAMERA::free::sensitivity] Definido! (%f)\n",w.sensitivity);
            }

            //Obter No Need Click
            const char* no_need_click = free->Attribute("noNeedClick");

            //No Need Click não existe
            if (no_need_click == nullptr) {
                fprintf(f,"[CAMERA::free::noNeedClick] Não existe\n");
            }
            else {

                if (strcasecmp("True",no_need_click) == 0)
                    w.free_needClick = false;

                fprintf(f,"[CAMERA::free::noNeedClick] Definido! (%d)\n",w.free_needClick);

            }

            //Obter Limited Angles
            const char* limited_angles = free->Attribute("limitedAngle");

            //Limited Angles não existe
            if (limited_angles == nullptr) {
                fprintf(f,"[CAMERA::free::limitedAngle] Não existe\n");
            }
            else {

                if (strcasecmp("False",limited_angles) == 0)
                    w.free_limitedAngle = false;

                fprintf(f,"[CAMERA::free::limitedAngle] Definido! (%d)\n",w.free_limitedAngle);

            }

            //Obter Velocidade da camera
            const char* speed = free->Attribute("speed");

            //Velocidade da camera não existe
            if (speed == nullptr) {
                fprintf(f,"[CAMERA::free::speed] Não existe\n");
            }
            else {
                w.free_speed = atof(speed);
                fprintf(f,"[CAMERA::free::speed] Definido! (%f)\n",w.free_speed);
            }

        }
        //Camera livre não existe
        else {
            fprintf(f,"[CAMERA::free] Não existe...\n");
        }


}

void processaXML_luz(FILE* f,World& w,TiXmlElement* luzes) {

    //Luzes não existem
    if (luzes == nullptr) {
        fprintf(f,"[LUZES] Não existe...\n");
        return;
    }
    else {

        //Obter luz
        TiXmlElement* luz = luzes->FirstChildElement("light");
        vector<Luz>* lista = new vector<Luz>();

        //Enquanto há luz, continua
        while (luz) {
        
            //Obter tipo
            const char* tipo_string = luz->Attribute("type");
        
            //tipo não existe
            if (tipo_string == nullptr) {
                fprintf(f,"[LUZ::tipo] Não existe\n");
            }
            else {

                //tipo existe
                string tipo = tipo_string;

                if (tipo == "point") {

                    float x,y,z;

                    //Obter posição x
                    const char* position_x = luz->Attribute("posx");

                    //Posição x não existe
                    if (position_x == nullptr) {
                        fprintf(f,"[LUZ::POINT::position::x] Não existe\n");
                    }
                    else {
                        x = atof(position_x);
                        fprintf(f,"[LUZ::POINT::position::x] Definido! (%f)\n",x);
                    }

                    //Obter posição y
                    const char* position_y = luz->Attribute("posy");

                    //Posição y não existe
                    if (position_y == nullptr) {
                        fprintf(f,"[LUZ::POINT::position::y] Não existe\n");
                    }
                    else {
                        y = atof(position_y);
                        fprintf(f,"[LUZ::POINT::position::y] Definido! (%f)\n",y);
                    }

                    //Obter posição z
                    const char* position_z = luz->Attribute("posz");

                    //Posição z não existe
                    if (position_z == nullptr) {
                        fprintf(f,"[LUZ::POINT::position::z] Não existe\n");
                    }
                    else {
                        z = atof(position_z);
                        fprintf(f,"[LUZ::POINT::position::z] Definido! (%f)\n",z);
                    }

                    lista->push_back(Luz::criarLuzPoint(x,y,z));

                }
                else if (tipo == "directional") {

                    float x,y,z;

                    //Obter direção x
                    const char* direction_x = luz->Attribute("dirx");

                    //Direção x não existe
                    if (direction_x == nullptr) {
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::x] Não existe\n");
                    }
                    else {
                        x = atof(direction_x);
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::x] Definido! (%f)\n",x);
                    }

                    //Obter direção y
                    const char* direction_y = luz->Attribute("diry");

                    //Direção y não existe
                    if (direction_y == nullptr) {
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::y] Não existe\n");
                    }
                    else {
                        y = atof(direction_y);
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::y] Definido! (%f)\n",y);
                    }

                    //Obter direção z
                    const char* direction_z = luz->Attribute("dirz");

                    //Direção z não existe
                    if (direction_z == nullptr) {
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::z] Não existe\n");
                    }
                    else {
                        z = atof(direction_z);
                        fprintf(f,"[LUZ::DIRECTIONAL::direction::z] Definido! (%f)\n",z);
                    }

                    lista->push_back(Luz::criarLuzDirectional(x,y,z));

                }
                else if (tipo == "spot") {

                    float pos_x,pos_y,pos_z,dir_x,dir_y,dir_z,cutoff;

                    //Obter posição x
                    const char* position_x = luz->Attribute("posx");

                    //Posição x não existe
                    if (position_x == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::position::x] Não existe\n");
                    }
                    else {
                        pos_x = atof(position_x);
                        fprintf(f,"[LUZ::SPOTLIGHT::position::x] Definido! (%f)\n",pos_x);
                    }

                    //Obter posição y
                    const char* position_y = luz->Attribute("posy");

                    //Posição y não existe
                    if (position_y == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::position::y] Não existe\n");
                    }
                    else {
                        pos_y = atof(position_y);
                        fprintf(f,"[LUZ::SPOTLIGHT::position::y] Definido! (%f)\n",pos_y);
                    }

                    //Obter posição z
                    const char* position_z = luz->Attribute("posz");

                    //Posição z não existe
                    if (position_z == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::position::z] Não existe\n");
                    }
                    else {
                        pos_z = atof(position_z);
                        fprintf(f,"[LUZ::SPOTLIGHT::position::z] Definido! (%f)\n",pos_z);
                    }

                    //Obter direção x
                    const char* direction_x = luz->Attribute("dirx");

                    //Direção x não existe
                    if (direction_x == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::x] Não existe\n");
                    }
                    else {
                        dir_x = atof(direction_x);
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::x] Definido! (%f)\n",dir_x);
                    }

                    //Obter direção y
                    const char* direction_y = luz->Attribute("diry");

                    //Direção y não existe
                    if (direction_y == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::y] Não existe\n");
                    }
                    else {
                        dir_y = atof(direction_y);
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::y] Definido! (%f)\n",dir_y);
                    }

                    //Obter direção z
                    const char* direction_z = luz->Attribute("dirz");

                    //Direção z não existe
                    if (direction_z == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::z] Não existe\n");
                    }
                    else {
                        dir_z = atof(direction_z);
                        fprintf(f,"[LUZ::SPOTLIGHT::direction::z] Definido! (%f)\n",dir_z);
                    }

                    //Obter cutoff
                    const char* cutoff_string = luz->Attribute("cutoff");

                    //Cutoff não existe
                    if (cutoff_string == nullptr) {
                        fprintf(f,"[LUZ::SPOTLIGHT::cutoff] Não existe\n");
                    }
                    else {
                        cutoff = atof(cutoff_string);
                        fprintf(f,"[LUZ::SPOTLIGHT::cutoff] Definido! (%f)\n",cutoff);
                    }


                    lista->push_back(Luz::criarLuzSpotlight(pos_x,pos_y,pos_z,dir_x,dir_y,dir_z,cutoff));

                }
                else {
                    fprintf(f,"[LUZ] Tipo desconhecido %s\n",tipo_string);
                }


            }
            
            //Coletar outra luz
            luz = luz->NextSiblingElement("light");
            
        }

        w.luzes = lista;

    }

}

//Função que processa as transformações de um grupo
Transform* processaXML_grupo_getTransformacao(FILE* f,World& w,int ID,TiXmlElement* grupo) {

    Transform* transformacao = nullptr;

    //Obter transformação
    TiXmlElement* transform = grupo->FirstChildElement("transform");
    
        //Transformação não existe
        if (transform == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::transform] Transformação não existe...\n",ID);
        }
        //Transformação existe
        else {

            //Obter elemento da transformação
            TiXmlElement* transform_elem = transform->FirstChildElement();
            transformacao = new Transform();

            //Enquanto há transformacoes, continua
            while (transform_elem) {
        
                //Obter tipo
                string tipo = transform_elem->Value();

                //Verifica se é translação
                if (tipo == "translate") {

                    const char* time_string = transform_elem->Attribute("time");
                
                    if (time_string != nullptr) { //animação
                        double time = atof(time_string) * 1000;
                        const char* align_string = transform_elem->Attribute("align");

                        bool align = false;
                        if (align_string != nullptr && (strcmp(align_string, "True") == 0 || strcmp(align_string, "true") == 0)) {
                            align = true;
                        }

                        const char* drawCurve_string = transform_elem->Attribute("drawCurve");

                        bool drawCurve = true;
                        if (drawCurve_string != nullptr && strcasecmp(drawCurve_string, "False") == 0 ) {
                            drawCurve = false;
                        }

                        fprintf(f,"[GRUPO::Nodo-%d::transform::translate] Animado - tempo = %f, align = %s, drawCurve = %s\n", ID, time/1000, align ? "true" : "false", drawCurve ? "true" : "false");

                        // Leer os pontos da curva
                        vector<Ponto>* pontos = new vector<Ponto>();
                        TiXmlElement* ponto_elem = transform_elem->FirstChildElement("point");

                        while (ponto_elem != nullptr) {
                            double px = atof(ponto_elem->Attribute("x"));
                            double py = atof(ponto_elem->Attribute("y"));
                            double pz = atof(ponto_elem->Attribute("z"));

                            pontos->push_back(Ponto(px, py, pz));
                            fprintf(f,"[GRUPO::Nodo-%d::translate::ponto] (%f, %f, %f)\n", ID, px, py, pz);

                            ponto_elem = ponto_elem->NextSiblingElement("point");
                        }

                        // Verificação mínima (4 pontos para Catmull-Rom)
                        if (pontos->size() >= 4) {

                            w.hasTime = true;
                            TransformElement t = TransformElement(TRANSLACAO,time,0,0,0,0,align,drawCurve,pontos);
                            transformacao->addTransform(t);
                        } else {
                            fprintf(f,"[ERRO::Nodo-%d::translate] Transformação animada requer pelo menos 4 pontos.\n", ID);
                        }
                    }

                    else { //estatico

                        double translate_x = 0, translate_y = 0, translate_z = 0;
        
                        //Obter X
                        const char* x_string = transform_elem->Attribute("x");
        
                        //X não existe
                        if (x_string == nullptr) {
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_x] Não existe\n",ID);
                        }
                        else {
                            translate_x = atof(x_string);
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_x] Definido! (%f)\n",ID,translate_x);
                        }
        
                        //Obter Y
                        const char* y_string = transform_elem->Attribute("y");
        
                        //Y não existe
                        if (y_string == nullptr) {
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_y] Não existe\n",ID);
                        }
                        else {
                            translate_y = atof(y_string);
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_y] Definido! (%f)\n",ID,translate_y);
                        }
        
                        //Obter Z
                        const char* z_string = transform_elem->Attribute("z");
        
                        //Z não existe
                        if (z_string == nullptr) {
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_z] Não existe\n",ID);
                        }
                        else {
                            translate_z = atof(z_string);
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::translate_z] Definido! (%f)\n",ID,translate_z);
                        }
        
                        //Adicionar translação
                        TransformElement t = TransformElement(TRANSLACAO,0,0,translate_x,translate_y,translate_z,false,false,nullptr);
                        transformacao->addTransform(t);

                    }
                
                } else {

                //Verifica se é rotação
                if (tipo == "rotate") {

                    double rotate_tempo = 0, rotate_angulo = 0, rotate_x = 0, rotate_y = 0, rotate_z = 0;

                    //Obter Angulo
                    const char* angulo_string = transform_elem->Attribute("angle");

                    //Angulo não existe
                    if (angulo_string == nullptr) {

                        //Obter Tempo
                        const char* tempo_string = transform_elem->Attribute("time");

                        //Tempo não existe
                        if (tempo_string == nullptr) {
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_angulo/time] Não existe\n",ID);
                        }
                        else {
                            rotate_tempo = atof(tempo_string) * 1000; //Para ser em milissegundos
                            w.hasTime = true;
                            fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_time] Definido! (%f)\n",ID,rotate_tempo/1000);
                        }

                    }
                    else {
                        rotate_angulo = atof(angulo_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_angulo] Definido! (%f)\n",ID,rotate_angulo);
                    }

                    //Obter X
                    const char* x_string = transform_elem->Attribute("x");

                    //X não existe
                    if (x_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_x] Não existe\n",ID);
                    }
                    else {
                        rotate_x = atof(x_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_x] Definido! (%f)\n",ID,rotate_x);
                    }

                    //Obter Y
                    const char* y_string = transform_elem->Attribute("y");

                    //Y não existe
                    if (y_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_y] Não existe\n",ID);
                    }
                    else {
                        rotate_y = atof(y_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_y] Definido! (%f)\n",ID,rotate_y);
                    }

                    //Obter Z
                    const char* z_string = transform_elem->Attribute("z");

                    //Z não existe
                    if (z_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_z] Não existe\n",ID);
                    }
                    else {
                        rotate_z = atof(z_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::rotate_z] Definido! (%f)\n",ID,rotate_z);
                    }

                    //Adicionar rotação
                    TransformElement t = TransformElement(ROTACAO,rotate_tempo,rotate_angulo,rotate_x,rotate_y,rotate_z,false,false,nullptr);
                    transformacao->addTransform(t);

                } else {

                //Verifica se é escala
                if (tipo == "scale") {

                    double scale_x = 0, scale_y = 0, scale_z = 0;

                    //Obter X
                    const char* x_string = transform_elem->Attribute("x");

                    //X não existe
                    if (x_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_x] Não existe\n",ID);
                    }
                    else {
                        scale_x = atof(x_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_x] Definido! (%f)\n",ID,scale_x);
                    }

                    //Obter Y
                    const char* y_string = transform_elem->Attribute("y");

                    //Y não existe
                    if (y_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_y] Não existe\n",ID);
                    }
                    else {
                        scale_y = atof(y_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_y] Definido! (%f)\n",ID,scale_y);
                    }

                    //Obter Z
                    const char* z_string = transform_elem->Attribute("z");

                    //Z não existe
                    if (z_string == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_z] Não existe\n",ID);
                    }
                    else {
                        scale_z = atof(z_string);
                        fprintf(f,"[GRUPOS::Nodo-%d::transform::scale_z] Definido! (%f)\n",ID,scale_z);
                    }

                    //Adicionar escala
                    TransformElement t = TransformElement(ESCALA,0,0,scale_x,scale_y,scale_z,false,false,nullptr);
                    transformacao->addTransform(t);

                }
                //Tipo inválido
                else {
                    fprintf(f,"[GRUPO::Node-%d::transform::type] Tipo %s não existe\n",ID,tipo.c_str());
                }}}
        
                //Coletar a próxima transformação
                transform_elem = transform_elem->NextSiblingElement();

            }
        }

    return transformacao;

}

//Função que processa as cores de um modelo
void processaXML_obterCorModelo(FILE* f,int ID,TiXmlElement* color,float* color_diffuse_r,float* color_diffuse_g,float* color_diffuse_b,float* color_ambient_r,float* color_ambient_g,float* color_ambient_b,float* color_specular_r,float* color_specular_g,float* color_specular_b,float* color_emissive_r,float* color_emissive_g,float* color_emissive_b,float* color_shininess) {

    //Obter Cor Difusa
    TiXmlElement* diffuse = color->FirstChildElement("diffuse");

    //Cor difusa não existe
    if (diffuse == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse] Não existe\n",ID);
    }
    else {

        //Obter Cor Difusa - Vermelho
        const char* diffuse_r = diffuse->Attribute("R");

        //Cor difusa vermelha não existe
        if (diffuse_r == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::red] Não existe\n",ID);
        }
        else {
            *color_diffuse_r = atof(diffuse_r);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::red] Definido (%f)\n",ID,*color_diffuse_r);
        }

        //Obter Cor Difusa - Verde
        const char* diffuse_g = diffuse->Attribute("G");

        //Cor difusa verde não existe
        if (diffuse_g == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::green] Não existe\n",ID);
        }
        else {
            *color_diffuse_g = atof(diffuse_g);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::green] Definido (%f)\n",ID,*color_diffuse_g);
        }

        //Obter Cor Difusa - Azul
        const char* diffuse_b = diffuse->Attribute("B");

        //Cor difusa azul não existe
        if (diffuse_b == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::blue] Não existe\n",ID);
        }
        else {
            *color_diffuse_b = atof(diffuse_b);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::diffuse::blue] Definido (%f)\n",ID,*color_diffuse_b);
        }

    }

    //Obter Cor Ambiente
    TiXmlElement* ambient = color->FirstChildElement("ambient");

    //Cor ambiente não existe
    if (ambient == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient] Não existe\n",ID);
    }
    else {

        //Obter Cor Ambiente - Vermelho
        const char* ambient_r = ambient->Attribute("R");

        //Cor ambiente vermelha não existe
        if (ambient_r == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::red] Não existe\n",ID);
        }
        else {
            *color_ambient_r = atof(ambient_r);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::red] Definido (%f)\n",ID,*color_ambient_r);
        }

        //Obter Cor Ambiente - Verde
        const char* ambient_g = ambient->Attribute("G");

        //Cor ambiente verde não existe
        if (ambient_g == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::green] Não existe\n",ID);
        }
        else {
            *color_ambient_g = atof(ambient_g);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::green] Definido (%f)\n",ID,*color_ambient_g);
        }

        //Obter Cor Ambiente - Azul
        const char* ambient_b = ambient->Attribute("B");

        //Cor ambiente azul não existe
        if (ambient_b == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::blue] Não existe\n",ID);
        }
        else {
            *color_ambient_b = atof(ambient_b);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::ambient::blue] Definido (%f)\n",ID,*color_ambient_b);
        }

    }

    //Obter Cor Especular
    TiXmlElement* specular = color->FirstChildElement("specular");

    //Cor especular não existe
    if (specular == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular] Não existe\n",ID);
    }
    else {

        //Obter Cor Especular - Vermelho
        const char* specular_r = specular->Attribute("R");

        //Cor especular vermelha não existe
        if (specular_r == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::red] Não existe\n",ID);
        }
        else {
            *color_specular_r = atof(specular_r);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::red] Definido (%f)\n",ID,*color_specular_r);
        }

        //Obter Cor Especular - Verde
        const char* specular_g = specular->Attribute("G");

        //Cor especular verde não existe
        if (specular_g == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::green] Não existe\n",ID);
        }
        else {
            *color_specular_g = atof(specular_g);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::green] Definido (%f)\n",ID,*color_specular_g);
        }

        //Obter Cor Especular - Azul
        const char* specular_b = specular->Attribute("B");

        //Cor especular azul não existe
        if (specular_b == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::blue] Não existe\n",ID);
        }
        else {
            *color_specular_b = atof(specular_b);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::specular::blue] Definido (%f)\n",ID,*color_specular_b);
        }

    }

    //Obter Cor Emissiva
    TiXmlElement* emissive = color->FirstChildElement("emissive");

    //Cor emissiva não existe
    if (emissive == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive] Não existe\n",ID);
    }
    else {

        //Obter Cor Emissiva - Vermelho
        const char* emissive_r = emissive->Attribute("R");

        //Cor emissiva vermelha não existe
        if (emissive_r == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::red] Não existe\n",ID);
        }
        else {
            *color_emissive_r = atof(emissive_r);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::red] Definido (%f)\n",ID,*color_emissive_r);
        }

        //Obter Cor Emissiva - Verde
        const char* emissive_g = emissive->Attribute("G");

        //Cor emissiva verde não existe
        if (emissive_g == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::green] Não existe\n",ID);
        }
        else {
            *color_emissive_g = atof(emissive_g);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::green] Definido (%f)\n",ID,*color_emissive_g);
        }

        //Obter Cor Emissiva - Azul
        const char* emissive_b = emissive->Attribute("B");

        //Cor emissiva azul não existe
        if (emissive_b == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::blue] Não existe\n",ID);
        }
        else {
            *color_emissive_b = atof(emissive_b);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::emissive::blue] Definido (%f)\n",ID,*color_emissive_b);
        }

    }

    //Obter Brilho
    TiXmlElement* shininess = color->FirstChildElement("shininess");

    //Brilho não existe
    if (shininess == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::shininess] Não existe\n",ID);
    }
    else {

        //Obter valor de brilho
        const char* shininess_string = shininess->Attribute("value");

        //Valor de brilho não existe
        if (shininess_string == nullptr) {
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::shininess::value] Não existe\n",ID);
        }
        else {
            *color_shininess = atof(shininess_string);
            fprintf(f,"[GRUPOS::Nodo-%d::models::model::color::shininess::value] Definido (%f)\n",ID,*color_shininess);
        }

    }


}

//Função que processa os modelos de um grupo
Models* processaXML_grupo_getModels(FILE* f,World& w,int ID,map<string,ModelSkeletonEngine*>* map,TiXmlElement* grupo) {

    Models* modelos = nullptr;

    //Modelos
    TiXmlElement* models = grupo->FirstChildElement("models");

    if (models == nullptr) {
        fprintf(f,"[GRUPOS::Nodo-%d::models] Modelos não existe...\n",ID);
    }
    else {

        //Obter model
        TiXmlElement* model = models->FirstChildElement("model");
        modelos = new Models();

        //Enquanto há model, continua
        while (model) {
        
            //Obter pathname
            const char* pathname = model->Attribute("file");
        
            //pathname não existe
            if (pathname == nullptr) {
                fprintf(f,"[GRUPO::Node-%d::models::model::file] Não existe\n",ID);
            }
            else {

                //pathname existe
                string file_path = pathname;
                //Modelo não existe no map
                if (map->count(file_path) == 0) {

                    ModelSkeletonEngine* modelo = lerBinario(file_path);

                    if (modelo != nullptr) {

                        (*map)[file_path] = modelo;
                        fprintf(f,"[GRUPO::Node-%d::models::model::file] Adicionado novo modelo %s!\n",ID,file_path.c_str());
                    }

                }

                //Inserir modelo
                if (map->count(file_path) > 0) {

                    ModelSkeletonEngine* esqueleto = (*map)[file_path];
                    char* model_texture = nullptr;
                    bool hasColor = false;
                    float color_diffuse_r = 200;
                    float color_diffuse_g = 200;
                    float color_diffuse_b = 200;
                    float color_ambient_r = 50;
                    float color_ambient_g = 50;
                    float color_ambient_b = 50;
                    float color_specular_r = 0;
                    float color_specular_g = 0;
                    float color_specular_b = 0;
                    float color_emissive_r = 0;
                    float color_emissive_g = 0;
                    float color_emissive_b = 0;
                    float color_shininess = 0;

                    //Obter Textura
                    TiXmlElement* texture = model->FirstChildElement("texture");

                    //Textura não existe
                    if (texture == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::models::model::texture] Não existe\n",ID);
                    }
                    else {

                        //Obter Ficheiro da Textura
                        const char* texture_file = texture->Attribute("file");
    
                        //Ficheiro da textura não existe
                        if (texture_file == nullptr) {
                            fprintf(f,"[GRUPOS::Nodo-%d::models::model::texture::file] Não existe\n",ID);
                        }
                        else {
                            model_texture = strdup(texture_file);
                            fprintf(f,"[GRUPOS::Nodo-%d::models::model::texture::file] Definido (%s)\n",ID,model_texture);
                        }

                    }

                    //Obter Cor
                    TiXmlElement* color = model->FirstChildElement("color");

                    //Cor não existe
                    if (color == nullptr) {
                        fprintf(f,"[GRUPOS::Nodo-%d::models::model::color] Não existe\n",ID);
                    }
                    else {

                        hasColor = true;
                        processaXML_obterCorModelo(f,ID,color,&color_diffuse_r,&color_diffuse_g,&color_diffuse_b,&color_ambient_r,&color_ambient_g,&color_ambient_b,&color_specular_r,&color_specular_g,&color_specular_b,&color_emissive_r,&color_emissive_g,&color_emissive_b,&color_shininess);

                    }

                    ModelElement* novo_modelo = new ModelElement(esqueleto,model_texture,hasColor,color_diffuse_r,color_diffuse_g,color_diffuse_b,color_ambient_r,color_ambient_g,color_ambient_b,color_specular_r,color_specular_g,color_specular_b,color_emissive_r,color_emissive_g,color_emissive_b,color_shininess);

                    modelos->addModel(novo_modelo);
                    fprintf(f,"[GRUPO::Node-%d::models::model::file] Adicionado modelo %s!\n",ID,file_path.c_str());
                
                }

            }
            
            //Coletar o outro model
            model = model->NextSiblingElement("model");
            
        }

    }

    return modelos;

}

//Função que processa grupos recursivamente
RoseTreeNode* processaXML_grupo_rec(FILE* f,World& w,int* ID,int ultimaTransformacao,map<string,ModelSkeletonEngine*>* map ,TiXmlElement* grupo) {

    //Atualizar as informações do nodo
    int ID_atual = *ID;
    (*ID)++;
    int ultimaTransformacaoFilhos = ultimaTransformacao;

    //Obter transformação do grupo
    Transform* transformacao = processaXML_grupo_getTransformacao(f,w,ID_atual,grupo);
    if (transformacao != nullptr)
        ultimaTransformacaoFilhos = ID_atual;

    //Obter modelos do grupo
    Models* modelos = processaXML_grupo_getModels(f,w,ID_atual,map,grupo);

    //Criar nodo
    RoseTreeNode* nodo = new RoseTreeNode(ID_atual,ultimaTransformacao);
    nodo->addModels(modelos);
    nodo->addTransform(transformacao);

    //Obter filho
    TiXmlElement* filho = grupo->FirstChildElement("group");

    //Enquanto há outros grupos
    while (filho) {
    
        //Obter filho
        RoseTreeNode* nodo_filho = processaXML_grupo_rec(f,w,ID,ultimaTransformacaoFilhos,map,filho);

        //Filho existe
        if (nodo_filho != nullptr) {

            nodo->addFilho(nodo_filho);
            fprintf(f,"[GRUPO::Nodo-%d::groups::filho] Adicionado filho (%d)...\n",ID_atual,nodo->ID);

        }

        //Coletar o outro filho
        filho = filho->NextSiblingElement("group");
    
    }

    fprintf(f,"[GRUPO::Nodo-%d::groups] Inserindo novo nodo (%d), cuja ultima transformação é %d e com %ld filhos\n",ID_atual,ID_atual,ultimaTransformacao,nodo->filhos.size());
    return nodo;

}

//Função que inicia o parser de grupos
void processaXML_grupo_init(FILE* f,World& w,TiXmlElement* grupo) {

    //Variavel que atribui automáticamente ID aos nodos
    int ID = 1;
    map<string,ModelSkeletonEngine*> modelos;
    
    //Grupo não existe
    if (grupo == nullptr) {
        fprintf(f,"[GRUPOS] Não existe...\n");
        return;
    }

    RoseTreeNode* arvore = processaXML_grupo_rec(f,w,&ID,0,&modelos,grupo);
    Groups* grupos = new Groups(arvore);
    w.grupos = grupos;

}

bool processaXML(World& w,TiXmlDocument xml) {

    //Extrair o "world"
    TiXmlElement* world = xml.FirstChildElement("world");

    //Criar ficheiro de log
    FILE* logger = fopen("xml_logger.txt","w");

    //Verifica se a criação do ficheiro aconteceu com sucesso
    if (logger == nullptr) {
        std::cerr << "Criação de ficheiro de logger de xml falhou\n";
        return false;
    }

    //World não existe
    if (world == nullptr) {
        std::cerr << "Erro: <world> não existe\n";
        return false;
    }
    
    //Processa Janela
    processaXML_janela(logger,w,world->FirstChildElement("window"));

    //Processa Camera
    processaXML_camera(logger,w,world->FirstChildElement("camera"));

    //Processa Luz
    processaXML_luz(logger,w,world->FirstChildElement("lights"));

    //Processa Grupo
    processaXML_grupo_init(logger,w,world->FirstChildElement("group"));

    fclose(logger);

    return true;

}