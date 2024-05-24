using System.ComponentModel.DataAnnotations;

namespace lei_loes.Models;

public class BilhetePremiumModel
{
    [Key]
    public string? BilheteID { get; set; }
    public DateTime DataAquisicao { get; set; }
    public bool Usado { get; set; }

}