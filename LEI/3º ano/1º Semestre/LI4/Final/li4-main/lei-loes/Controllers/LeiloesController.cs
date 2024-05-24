using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using lei_loes.Data;
using lei_loes.Models;
using Microsoft.AspNetCore.Identity;

namespace lei_loes.Controllers
{
    public class LeiloesController : Controller
    {
        private readonly ApplicationDbContext _context;
        private readonly UserManager<User> _userManager;


        public LeiloesController(ApplicationDbContext context, UserManager<User> userManager)
        {
            _context = context;
            _userManager = userManager;
        }
        public async Task<IActionResult> Index()
        {
            var inicioDoMes = new DateTime(DateTime.Now.Year, DateTime.Now.Month, 1);

            var fimDoMes = inicioDoMes.AddMonths(1).AddDays(-1);

            var leiloesNoMes = await _context.LeilaoModel
                .Where(l => l.DataInicio >= inicioDoMes && l.DataFim <= fimDoMes)
                .ToListAsync();

            if (!leiloesNoMes.Any())
            {
                ViewBag.Message = "Não há leilões este mês.";
            }

            return View(leiloesNoMes);
        }


       
        public async Task<IActionResult> Calendario()
            {
                var leiloesNoMes = await _context.LeilaoModel
                        .Where(l => l.DataInicio.Month == DateTime.Now.Month)
                        .ToListAsync();
                return View(leiloesNoMes);
            }
        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var leilaoModel = await _context.LeilaoModel
                .FirstOrDefaultAsync(m => m.LeilaoID == id);
            if (leilaoModel == null)
            {
                return NotFound();
            }

            return View(leilaoModel);
        }
        
  
        public async Task UpdateValorInicial(string leilaoID)
        {
            var leilaoModel = await _context.LeilaoModel.FirstOrDefaultAsync(m => m.LeilaoID == leilaoID);

            if (leilaoModel != null)
            {
                var carroModel = await _context.CarroModel.FirstOrDefaultAsync(m => m.CarroID == leilaoModel.Carro_CarroID);

                if (carroModel != null)
                {
                    leilaoModel.PrecoInicial = carroModel.PrecoInicial;

                    await _context.SaveChangesAsync();
                }
            }
        }

        public IActionResult Create()
        {
            ViewBag.Carro_CarroID = new SelectList(_context.CarroModel, "CarroID", "Marca");
            var admin = _userManager.GetUserAsync(User).Result;
            if (admin == null)
            {
                return Challenge();
            }

            var leilaoModel = new LeilaoModel
            {
                DataInicio = DateTime.Now,
                DataFim = DateTime.Now
            };

            return View(leilaoModel);
        }


        [HttpPost]
[ValidateAntiForgeryToken]
public async Task<IActionResult> Create(LeilaoModel leilaoModel)
{
    ViewBag.Carro_CarroID = new SelectList(_context.CarroModel, "CarroID", "Marca");
    if (ModelState.IsValid)
    {
        if (string.IsNullOrEmpty(leilaoModel.LeilaoID))
        {
            leilaoModel.LeilaoID = Guid.NewGuid().ToString();
        }
        leilaoModel.Admin_AdminID = _userManager.GetUserId(User);
        leilaoModel.PrecoInicial = _context.CarroModel.FirstOrDefault(c => c.CarroID == leilaoModel.Carro_CarroID).PrecoInicial;
        _context.Add(leilaoModel);
        await _context.SaveChangesAsync();
        return RedirectToAction(nameof(Index));
    }
    ViewBag.Carro_CarroID = new SelectList(_context.CarroModel, "CarroID", "NomeDoCarro", leilaoModel.Carro_CarroID);
    return View(leilaoModel);
}



        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id, [Bind("LeilaoID,DataInicio,DataFim,ExclusividadeLeilao,TipoLeilao,Carro_CarroID,Funcionario_IDFuncionario")] LeilaoModel leilaoModel)
        {
            if (id != leilaoModel.LeilaoID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(leilaoModel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!LeilaoModelExists(leilaoModel.LeilaoID))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(leilaoModel);
        }

        public async Task<IActionResult> Delete(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var leilaoModel = await _context.LeilaoModel
                .FirstOrDefaultAsync(m => m.LeilaoID == id);
            if (leilaoModel == null)
            {
                return NotFound();
            }

            return View(leilaoModel);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var leilaoModel = await _context.LeilaoModel.FindAsync(id);
            if (leilaoModel != null)
            {
                _context.LeilaoModel.Remove(leilaoModel);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool LeilaoModelExists(string id)
        {
            return _context.LeilaoModel.Any(e => e.LeilaoID == id);
        }
        public async Task<IActionResult> Detalhes(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var leilaoModel = await _context.LeilaoModel
                .FirstOrDefaultAsync(m => m.LeilaoID == id);
            if (leilaoModel == null)
            {
                return NotFound();
            }

            return View(leilaoModel);
        }
        


        public IActionResult Lista()
        {
            List<LeilaoModel> leiloes = _context.LeilaoModel.ToList();

            return View(leiloes);
        }
        public async Task<IActionResult> Edit(string id)
{
    if (id == null)
    {
        return NotFound();
    }

    var leilaoModel = await _context.LeilaoModel.FindAsync(id);
    if (leilaoModel == null)
    {
        return NotFound();
    }
    return View(leilaoModel);
}


    }
}
