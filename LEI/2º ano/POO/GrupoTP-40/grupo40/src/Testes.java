import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Map;

import Model.Alongamentos;
import Model.BodyPart;
import Model.Btt;
import Model.CorridaTerreno;
import Model.Fitness;
import Model.Genero;
import Model.PeriodicidadePlano;
import Model.Pesos;
import Model.PlanoTreino;
import Model.Remo;
import Model.TipoTerreno;
import Model.UserAmador;
import Model.UserOcasional;
import Model.UserProfissional;
import Model.Utilizador;

public class Testes {
    
    public static void main(String[] args) throws FileNotFoundException, IOException, ClassNotFoundException {
        Fitness f = new Fitness();


        Utilizador u1 = new UserProfissional("u1@mail.pt", "u1", "Tiago", Genero.Masculino, 1.75, 70.0, LocalDate.of(1998, 2, 5));
        Utilizador u2 = new UserProfissional("u2@mail.pt", "u2", "Lúcia", Genero.Feminino, 1.78, 66.0, LocalDate.of(1984, 8, 15));
        Utilizador u3 = new UserProfissional("u3@mail.pt", "u3", "Rúben", Genero.Masculino, 1.8, 70.0, LocalDate.of(1975, 11, 24));
        Utilizador u4 = new UserOcasional("u4@mail.pt", "u4", "Catarina", Genero.Feminino, 1.65, 65.0, LocalDate.of(1983, 12, 10));
        Utilizador u5 = new UserOcasional("u5@mail.pt", "u5", "Agostinho", Genero.Masculino, 1.82, 80.0, LocalDate.of(1996, 7, 1));
        Utilizador u6 = new UserOcasional("u6@mail.pt", "u6", "Joana", Genero.Feminino, 1.7, 58.0, LocalDate.of(2007, 1, 5));
        Utilizador u7 = new UserAmador("u7@mail.pt", "u7", "António", Genero.Masculino, 1.9, 85.0, LocalDate.of(1965, 2, 28));
        Utilizador u8 = new UserAmador("u8@mail.pt", "u8", "Sofia", Genero.Feminino, 1.55, 50.0, LocalDate.of(2003, 6, 11));
        Utilizador u9 = new UserAmador("u9@mail.pt", "u9", "José", Genero.Masculino, 1.83, 87.0, LocalDate.of(2002, 3, 31));
        
    
        CorridaTerreno c1 = new CorridaTerreno("CorridaMontanha", LocalDateTime.of(2024, 5, 1, 10, 0), (long) 150, u1, 4000.0, 100.0, TipoTerreno.MONTE);
        CorridaTerreno c2 = new CorridaTerreno("CorridaEstrada", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 120, u2, 3000.0, 100.0, TipoTerreno.ESTRADA);
        CorridaTerreno c3 = new CorridaTerreno("CorridaPista", LocalDateTime.of(2024, 3, 1, 10, 0), (long) 180, u3, 5000.0, 50.0, TipoTerreno.PISTA);
        CorridaTerreno c4 = new CorridaTerreno("CorridaTrilho", LocalDateTime.of(2024, 5, 15, 10, 0), (long) 120, u4, 2000.0, 200.0, TipoTerreno.TRILHO);
        CorridaTerreno c5 = new CorridaTerreno("CorridaMontanha", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 160, u5, 4000.0, 100.0, TipoTerreno.MONTE);
        CorridaTerreno c6 = new CorridaTerreno("CorridaEstrada", LocalDateTime.of(2024, 5, 15, 10, 0), (long) 120, u6, 3000.0, 100.0, TipoTerreno.ESTRADA);
        CorridaTerreno c7 = new CorridaTerreno("CorridaPista", LocalDateTime.of(2024, 5, 1, 10, 0), (long) 200, u7, 5000.0, 50.0, TipoTerreno.PISTA);
        CorridaTerreno c8 = new CorridaTerreno("CorridaTrilho", LocalDateTime.of(2024, 3, 15, 10, 0), (long) 120, u8, 2000.0, 200.0, TipoTerreno.TRILHO);
        CorridaTerreno c9 = new CorridaTerreno("CorridaMontanha", LocalDateTime.of(2024, 1, 1, 10, 0), (long) 150, u9, 4000.0, 100.0, TipoTerreno.MONTE);

        u1.addAtividade(c1);
        u2.addAtividade(c2);
        u3.addAtividade(c3);
        u4.addAtividade(c4);
        u5.addAtividade(c5);
        u6.addAtividade(c6);
        u7.addAtividade(c7);
        u8.addAtividade(c8);
        u9.addAtividade(c9);


        Alongamentos a1 = new Alongamentos("Alongamento1", LocalDateTime.of(2024, 2, 1, 10, 0), (long) 60, u1, 10, 3, BodyPart.SUPERIORES);
        Alongamentos a2 = new Alongamentos("Alongamento2", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 30, u2, 10, 3, BodyPart.INFERIORES);
        Alongamentos a3 = new Alongamentos("Alongamento3", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 20, u3, 10, 3, BodyPart.TRONCO);
        Alongamentos a4 = new Alongamentos("Alongamento4", LocalDateTime.of(2024, 5, 15, 10, 0), (long) 10, u4, 10, 3, BodyPart.INFERIORES);
        Alongamentos a5 = new Alongamentos("Alongamento5", LocalDateTime.of(2024, 5, 1, 10, 0), (long) 30, u5, 10, 3, BodyPart.SUPERIORES);
        Alongamentos a6 = new Alongamentos("Alongamento6", LocalDateTime.of(2024, 3, 15, 10, 0), (long) 25, u6, 10, 3, BodyPart.INFERIORES);
        Alongamentos a7 = new Alongamentos("Alongamento7", LocalDateTime.of(2024, 1, 1, 10, 0), (long) 15, u7, 10, 3, BodyPart.TRONCO);
        Alongamentos a8 = new Alongamentos("Alongamento8", LocalDateTime.of(2024, 1, 15, 10, 0), (long) 30, u8, 10, 3, BodyPart.OUTRO);
        Alongamentos a9 = new Alongamentos("Alongamento9", LocalDateTime.of(2024, 1, 1, 10, 0), (long) 5, u9, 10, 3, BodyPart.SUPERIORES);
        
        u1.addAtividade(a1);
        u2.addAtividade(a2);
        u3.addAtividade(a3);
        u4.addAtividade(a4);
        u5.addAtividade(a5);
        u6.addAtividade(a6);
        u7.addAtividade(a7);
        u8.addAtividade(a8);
        u9.addAtividade(a9);
        
        Btt b1 = new Btt("Btt1", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 150, u1, 4000.0, 500.0,TipoTerreno.MONTE ,4);
        Btt b2 = new Btt("Btt2", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 120, u2, 3000.0, 400.0,TipoTerreno.MONTE ,3);
        Btt b3 = new Btt("Btt3", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 180, u3, 5000.0, 300.0,TipoTerreno.MONTE ,5);

        u1.addAtividade(b1);
        u2.addAtividade(b2);
        u3.addAtividade(b3);

     
        Pesos p1 = new Pesos("Braços", LocalDateTime.of(2024, 2, 1, 10, 0), (long) 150, u1, 50.0, 15, 4);
        Pesos p2 = new Pesos("LegPress", LocalDateTime.of(2024, 3, 15, 10, 0), (long) 120, u2, 60.0, 10, 3);
        Pesos p3 = new Pesos("Costas", LocalDateTime.of(2024, 3, 1, 10, 0), (long) 180, u3, 35.0, 10, 5);
        Pesos p4 = new Pesos("Supino", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 120, u4, 40.0, 12, 3);
        Pesos p5 = new Pesos("Pernas", LocalDateTime.of(2024, 5, 1, 10, 0), (long) 160, u5, 70.0, 8, 4);
        Pesos p6 = new Pesos("Agachamento", LocalDateTime.of(2024, 2, 15, 10, 0), (long) 120, u6, 10.0, 10, 3);
        Pesos p7 = new Pesos("Puxador", LocalDateTime.of(2024, 1, 1, 10, 0), (long) 200, u7, 30.0, 10, 5);
        Pesos p8 = new Pesos("Prensa", LocalDateTime.of(2024, 3, 15, 10, 0), (long) 120, u8, 50.0, 12, 3);
        Pesos p9 = new Pesos("Biceps", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 150, u9, 20.0, 15, 4);


        u1.addAtividade(p1);
        u2.addAtividade(p2);
        u3.addAtividade(p3);
        u4.addAtividade(p4);
        u5.addAtividade(p5);
        u6.addAtividade(p6);
        u7.addAtividade(p7);
        u8.addAtividade(p8);
        u9.addAtividade(p9);


        Remo r1 = new Remo("Canoagem", LocalDateTime.of(2024, 1, 1, 10, 0), (long) 150, u1, 4000.0);
        Remo r2 = new Remo("Canoagem", LocalDateTime.of(2024, 3, 15, 10, 0), (long) 120, u2, 3000.0);
        Remo r3 = new Remo("Canoagem", LocalDateTime.of(2024, 2, 1, 10, 0), (long) 180, u3, 5000.0);
        Remo r4 = new Remo("Canoagem", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 120, u4, 2000.0);
        Remo r5 = new Remo("Canoagem", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 160, u5, 4000.0);
        Remo r6 = new Remo("Canoagem", LocalDateTime.of(2024, 1, 15, 10, 0), (long) 120, u6, 3000.0);
        Remo r7 = new Remo("Canoagem", LocalDateTime.of(2024, 5, 1, 10, 0), (long) 200, u7, 5000.0);
        Remo r8 = new Remo("Canoagem", LocalDateTime.of(2024, 4, 15, 10, 0), (long) 120, u8, 2000.0);
        Remo r9 = new Remo("Canoagem", LocalDateTime.of(2024, 4, 1, 10, 0), (long) 150, u9, 4000.0);

        u1.addAtividade(r1);
        u2.addAtividade(r2);
        u3.addAtividade(r3);
        u4.addAtividade(r4);
        u5.addAtividade(r5);
        u6.addAtividade(r6);
        u7.addAtividade(r7);
        u8.addAtividade(r8);
        u9.addAtividade(r9);

        f.adduser(u1);
         f.adduser(u2);
            f.adduser(u3);
                f.adduser(u4);
                    f.adduser(u5);
                        f.adduser(u6);
                            f.adduser(u7);
                            f.adduser(u8);
                                f.adduser(u9);

        CorridaTerreno c10 = new CorridaTerreno("CorridaMontanha", LocalDateTime.of(2024, 8, 1, 10, 0), (long) 150, 4000.0, 100.0, TipoTerreno.MONTE);
        CorridaTerreno c11 = new CorridaTerreno("CorridaEstrada", LocalDateTime.of(2024, 6, 15, 10, 0), (long) 120, 3000.0, 100.0, TipoTerreno.ESTRADA);
        CorridaTerreno c12 = new CorridaTerreno("CorridaPista", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 180, 5000.0, 50.0, TipoTerreno.PISTA);

        Alongamentos a10 = new Alongamentos("Alongamento10", LocalDateTime.of(2024, 8, 1, 10, 0), (long) 60, 10, 3, BodyPart.SUPERIORES);
        Alongamentos a11 = new Alongamentos("Alongamento11", LocalDateTime.of(2024, 6, 15, 10, 0), (long) 30, 10, 3, BodyPart.INFERIORES);
        Alongamentos a12 = new Alongamentos("Alongamento12", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 20, 10, 3, BodyPart.TRONCO);

        Btt b4 = new Btt("Btt4", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 150, 4000.0, 500.0,TipoTerreno.MONTE ,4);
        Btt b5 = new Btt("Btt5", LocalDateTime.of(2024, 6, 15, 10, 0), (long) 120, 3000.0, 400.0,TipoTerreno.MONTE ,3);
        Btt b6 = new Btt("Btt6", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 180, 5000.0, 300.0,TipoTerreno.MONTE ,5);

        Pesos p10 = new Pesos("Braços", LocalDateTime.of(2024, 7, 1, 10, 0), (long) 150, 50.0, 15, 4);
        Pesos p11 = new Pesos("LegPress", LocalDateTime.of(2024, 7, 1, 10, 0), (long) 120, 60.0, 10, 3);
        Pesos p12 = new Pesos("Costas", LocalDateTime.of(2024, 7, 1, 10, 0), (long) 180, 35.0, 10, 5);

        Remo r10 = new Remo("Canoagem", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 150, 4000.0);
        Remo r11 = new Remo("Canoagem", LocalDateTime.of(2024, 6, 15, 10, 0), (long) 120, 3000.0);
        Remo r12 = new Remo("Canoagem", LocalDateTime.of(2024, 6, 1, 10, 0), (long) 180, 5000.0);
        
        f.addAtividade(c10);
        f.addAtividade(c11);
        f.addAtividade(c12);
        f.addAtividade(a10);
        f.addAtividade(a11);
        f.addAtividade(a12);
        f.addAtividade(b4);
        f.addAtividade(b5);
        f.addAtividade(b6);
        f.addAtividade(p10);
        f.addAtividade(p11);
        f.addAtividade(p12);
        f.addAtividade(r10);
        f.addAtividade(r11);
        f.addAtividade(r12);

        PlanoTreino pt1 = new PlanoTreino(LocalDate.of(2024, 8, 1), PeriodicidadePlano.SEMANAL);
        PlanoTreino pt2 = new PlanoTreino(LocalDate.of(2024, 6, 15), PeriodicidadePlano.MENSAL);
        PlanoTreino pt3 = new PlanoTreino(LocalDate.of(2024, 6, 1), PeriodicidadePlano.SEMANAL);

        pt1.addAtividade(c10);
        pt1.addAtividade(a10);
        
        pt2.addAtividade(c11);
        pt2.addAtividade(a11);

        pt3.addAtividade(c12);
        pt3.addAtividade(a12);

        f.addPlanoTreino(pt1);
        f.addPlanoTreino(pt2);
        f.addPlanoTreino(pt3);

        PlanoTreino pt4 = new PlanoTreino(LocalDate.of(2024, 7, 1), PeriodicidadePlano.SEMANAL);
        pt4.addAtividade(p10);
        pt4.addAtividade(p11);
        pt4.addAtividade(p12);

        PlanoTreino pt5 = new PlanoTreino(LocalDate.of(2024, 7, 1), PeriodicidadePlano.SEMANAL);
        pt5.addAtividade(b4);

        PlanoTreino pt6 = new PlanoTreino(LocalDate.of(2024, 7, 1), PeriodicidadePlano.SEMANAL);
        pt6.addAtividade(r10);
        pt6.addAtividade(r11);

        f.addPlanoTreino(pt1);
        f.addPlanoTreino(pt2);
        f.addPlanoTreino(pt3);
        f.addPlanoTreino(pt4);
        f.addPlanoTreino(pt5);
        f.addPlanoTreino(pt6);

        f.guardaEstadoBin("simulacao.dat");
        f.guardaAtividades("Atividades.dat");
        f.guardaUtilizadores("Utilizadores.dat");
        f.guardaPlanosTreino("PlanoTreino.dat");

        f.guardaEstadoCSV("simulacao.csv");
        f.escreverCSVAtividades("Atividades.csv");
        f.escreverCSVUtilizadores("Utilizadores.csv");
        f.escreverCSVPlanosTreino("PlanoTreino.csv");

    }
}
