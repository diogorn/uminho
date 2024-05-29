using System.ComponentModel.DataAnnotations;

namespace lei_loes.Models;
public class CarroModel
{
    [Key]
    public string CarroID { get; set; } = String.Empty;
    [Required]
    public string Marca { get; set; } = String.Empty;
    [Required]
    public string Modelo { get; set; } = String.Empty;
    [Required]
    public string Descricao { get; set; } = String.Empty;
    [Required]
    public float PrecoInicial { get; set; }

    
}