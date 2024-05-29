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
    public class BilhetePremiumController : Controller
    {
        private readonly ApplicationDbContext _context;

        public BilhetePremiumController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            return View(await _context.BilhetePremiumModel.ToListAsync());
        }

        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bilhetePremiumModel = await _context.BilhetePremiumModel
                .FirstOrDefaultAsync(m => m.BilheteID == id);
            if (bilhetePremiumModel == null)
            {
                return NotFound();
            }

            return View(bilhetePremiumModel);
        }

        public IActionResult Create()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BilheteID,DataAquisicao,Usado")] BilhetePremiumModel bilhetePremiumModel)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bilhetePremiumModel);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(bilhetePremiumModel);
        }

        public async Task<IActionResult> Edit(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bilhetePremiumModel = await _context.BilhetePremiumModel.FindAsync(id);
            if (bilhetePremiumModel == null)
            {
                return NotFound();
            }
            return View(bilhetePremiumModel);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id, [Bind("BilheteID,DataAquisicao,Usado")] BilhetePremiumModel bilhetePremiumModel)
        {
            if (id != bilhetePremiumModel.BilheteID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(bilhetePremiumModel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!BilhetePremiumModelExists(bilhetePremiumModel.BilheteID))
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
            return View(bilhetePremiumModel);
        }

        public async Task<IActionResult> Delete(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bilhetePremiumModel = await _context.BilhetePremiumModel
                .FirstOrDefaultAsync(m => m.BilheteID == id);
            if (bilhetePremiumModel == null)
            {
                return NotFound();
            }

            return View(bilhetePremiumModel);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var bilhetePremiumModel = await _context.BilhetePremiumModel.FindAsync(id);
            if (bilhetePremiumModel != null)
            {
                _context.BilhetePremiumModel.Remove(bilhetePremiumModel);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool BilhetePremiumModelExists(string id)
        {
            return _context.BilhetePremiumModel.Any(e => e.BilheteID == id);
        }
    }
}
