using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using lei_loes.Data;
using lei_loes.Models;

namespace lei_loes.Controllers
{
    public class CarrosController : Controller
    {
        private readonly ApplicationDbContext _context;

        public CarrosController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            return View(await _context.CarroModel.ToListAsync());
        }

        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var carroModel = await _context.CarroModel
                .FirstOrDefaultAsync(m => m.CarroID == id);
            if (carroModel == null)
            {
                return NotFound();
            }

            return View(carroModel);
        }

         public IActionResult Create()
        {
            var carro = new CarroModel
            {
                CarroID = Guid.NewGuid().ToString() 
            };

            return View(carro); 
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("CarroID,Marca,Modelo,Descricao,PrecoInicial")] CarroModel carroModel)
        {
            if (ModelState.IsValid)
            {
                _context.Add(carroModel);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(carroModel);
        }

        public async Task<IActionResult> Edit(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var carroModel = await _context.CarroModel.FindAsync(id);
            if (carroModel == null)
            {
                return NotFound();
            }
            return View(carroModel);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id, [Bind("CarroID,Marca,Modelo,Descricao,PrecoInicial")] CarroModel carroModel)
        {
            if (id != carroModel.CarroID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(carroModel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!CarroModelExists(carroModel.CarroID))
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
            return View(carroModel);
        }

        public async Task<IActionResult> Delete(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var carroModel = await _context.CarroModel
                .FirstOrDefaultAsync(m => m.CarroID == id);
            if (carroModel == null)
            {
                return NotFound();
            }

            return View(carroModel);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var carroModel = await _context.CarroModel.FindAsync(id);
            if (carroModel != null)
            {
                _context.CarroModel.Remove(carroModel);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool CarroModelExists(string id)
        {
            return _context.CarroModel.Any(e => e.CarroID == id);
        }

        public IActionResult Lista()
        {
            
            var carros = _context.CarroModel.ToList(); 

            return View(carros); 
        }
    }
    

}
