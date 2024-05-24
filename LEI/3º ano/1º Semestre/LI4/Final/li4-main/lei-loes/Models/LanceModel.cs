using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace lei_loes.Models;

public class LanceModel
{
    [Key]
    public string LanceID { get; set; } = String.Empty;
    [Required]
    public float Valor { get; set; } = 0;
    public string Cliente_ClienteID { get; set; } = String.Empty;
    public string Leilao_LeilaoID { get; set; } = String.Empty;
}
