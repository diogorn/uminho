using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Identity;

namespace lei_loes.Data;

public class User : IdentityUser
{
  
    public string Nome { get; set; } = String.Empty;
  
    public bool Anonimo { get; set; } = false;
   
    public bool Premium { get; set; } = false;
    public string? BilhetePremium_BilheteID { get; set; }
    public bool Admin { get; set; } = false;
    
}