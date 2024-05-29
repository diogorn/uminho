using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using lei_loes.Data;
using lei_loes.Models;
using lei_loes.Controllers;
using Microsoft.AspNetCore.Identity;
using Microsoft.CodeAnalysis.Editing;

namespace lei_loes.Controllers
{
    public class LancesController : Controller
    {

        private readonly ApplicationDbContext _context;
        private readonly UserManager<User> _userManager;

        public LancesController(ApplicationDbContext context, UserManager<User> userManager)
        {
            _context = context;
            _userManager = userManager;
        }

        public async Task<IActionResult> Index()
        {
            return View(await _context.LanceModel.ToListAsync());
        }


        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var lanceModel = await _context.LanceModel
                .FirstOrDefaultAsync(m => m.LanceID == id);
            if (lanceModel == null)
            {
                return NotFound();
            }

            return View(lanceModel);
        }

        public async Task<IActionResult> Create()
        {
            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return Challenge(); 
            }

            ViewBag.Cliente_ClienteID = user.Id;
            ViewBag.Leilao_LeilaoID = new SelectList(_context.LeilaoModel, "LeilaoID", "LeilaoID");

            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Valor,Cliente_ClienteID,Leilao_LeilaoID")] LanceModel lanceModel)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    using (var transaction = _context.Database.BeginTransaction())
                    {
                        var leilaoModel = await _context.LeilaoModel
                            .FromSqlRaw("SELECT * FROM LeilaoModel WITH (UPDLOCK) WHERE LeilaoID = {0}", lanceModel.Leilao_LeilaoID)
                            .FirstOrDefaultAsync();

                        if (lanceModel.Valor > leilaoModel.PrecoInicial && lanceModel.Valor > leilaoModel.PrecoAtual)
                        {
                            lanceModel.LanceID = Guid.NewGuid().ToString();

                            leilaoModel.PrecoAtual = lanceModel.Valor;

                            _context.Add(lanceModel);

                            _context.Update(leilaoModel);


                            await _context.SaveChangesAsync();



                            transaction.Commit();

                            return RedirectToAction(nameof(lei_loes.Controllers.LeiloesController.Detalhes), "Leiloes", new { id = leilaoModel.LeilaoID });
                        }
                        else
                        {
                            ModelState.AddModelError("Valor", "O valor do lance deve ser maior que o lance atual ou o valor inicial do carro.");
                        }
                    }
                }
                catch (DbUpdateException)
                {
                    ModelState.AddModelError(string.Empty, "Outro usuário está atualmente fazendo um lance neste leilão. Por favor, tente novamente em alguns momentos.");
                }
            }

            ViewBag.Leilao_LeilaoID = new SelectList(_context.LeilaoModel, "LeilaoID", "LeilaoID");

            return View(lanceModel);
        }


        [HttpGet]
        public async Task<IActionResult> Lanca(string leilaoId)
        {
            var user = await _userManager.GetUserAsync(User);

            if (user == null)
            {
                return Challenge(); 
            }

            var viewModel = new LanceModel
            {
                Cliente_ClienteID = user.Id,
                Leilao_LeilaoID = leilaoId
            };

            return View(viewModel);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Lanca(LanceModel viewModel)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    using (var transaction = _context.Database.BeginTransaction())
                    {
                        var leilaoModel = await _context.LeilaoModel
                            .FromSqlRaw("SELECT * FROM LeilaoModel WITH (UPDLOCK) WHERE LeilaoID = {0}", viewModel.Leilao_LeilaoID)
                            .FirstOrDefaultAsync();

                        if (viewModel.Valor > leilaoModel.PrecoInicial && viewModel.Valor > leilaoModel.PrecoAtual)
                        {
                            var lanceModel = new LanceModel
                            {
                                LanceID = Guid.NewGuid().ToString(),
                                Valor = viewModel.Valor,
                                Cliente_ClienteID = viewModel.Cliente_ClienteID,
                                Leilao_LeilaoID = viewModel.Leilao_LeilaoID
                            };

                            leilaoModel.PrecoAtual = viewModel.Valor;

                            _context.Add(lanceModel);
                            _context.Update(leilaoModel);
                            await _context.SaveChangesAsync();

                            transaction.Commit();

                            TempData["SuccessMessage"] = "Lance realizado com sucesso!";
                            return RedirectToAction(nameof(LeiloesController.Detalhes), "Leiloes", new { id = leilaoModel.LeilaoID });
                        }
                        else
                        {
                            ModelState.AddModelError("Valor", "O valor do lance deve ser maior que o lance atual ou o valor inicial do carro.");
                        }
                    }
                }
                catch (DbUpdateException)
                {
                    ModelState.AddModelError(string.Empty, "Outro utilizador está a fazer um lance neste leilão. Por favor, tente novamente mais tarde.");
                }
                catch (Exception)
                {
                    ModelState.AddModelError(string.Empty, "Ocorreu um erro ao processar o lance. Por favor, tente novamente.");
                }
            }

            return View(viewModel);
        }


        public async Task<IActionResult> Edit(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var lanceModel = await _context.LanceModel.FindAsync(id);
            if (lanceModel == null)
            {
                return NotFound();
            }

            var user = await _userManager.GetUserAsync(User);
            if (user == null)
            {
                return Challenge(); 
            }

            ViewBag.Cliente_ClienteID = user.Id;
            ViewBag.Leilao_LeilaoID = new SelectList(_context.LeilaoModel, "LeilaoID", "LeilaoID");

            return View(lanceModel);
        }



        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id,
            [Bind("LanceID,Valor,Cliente_ClienteID,Leilao_LeilaoID")] LanceModel lanceModel)
        {
            if (id != lanceModel.LanceID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(lanceModel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!LanceModelExists(lanceModel.LanceID))
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

            return View(lanceModel);
        }

        public async Task<IActionResult> Delete(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var lanceModel = await _context.LanceModel
                .FirstOrDefaultAsync(m => m.LanceID == id);
            if (lanceModel == null)
            {
                return NotFound();
            }

            return View(lanceModel);
        }

        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var lanceModel = await _context.LanceModel.FindAsync(id);
            if (lanceModel != null)
            {
                _context.LanceModel.Remove(lanceModel);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool LanceModelExists(string id)
        {
            return _context.LanceModel.Any(e => e.LanceID == id);
        }
    }
}
