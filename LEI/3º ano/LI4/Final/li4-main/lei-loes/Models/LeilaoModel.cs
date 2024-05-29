using System.ComponentModel.DataAnnotations;
using lei_loes.Data;
using NuGet.Versioning;

namespace lei_loes.Models;

public class LeilaoModel
{
    [Key]
    public string? LeilaoID { get; set; }
    public DateTime DataInicio { get; set; }
    public DateTime DataFim { get; set; }

    public string? TipoLeilao { get; set; }
    public float PrecoInicial { get; set; }
    public float PrecoAtual { get; set; }
    public float PrecoFinal { get; set; }
    public bool ExclusividadeLeilao { get; set; }

    public string? Carro_CarroID { get; set; }
    public virtual CarroModel? Carro { get; set; }
    public string? Admin_AdminID { get; set; }

}