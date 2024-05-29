using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Linq;
using System.Threading.Tasks;
using lei_loes.Data;
using Microsoft.EntityFrameworkCore;

namespace lei_loes.Controllers
{
    public class UserController : Controller
    {
        private readonly UserManager<User> _userManager;

        public UserController(UserManager<User> userManager)
        {
            _userManager = userManager;
        }

        public async Task<IActionResult> ListUsers()
        {
            var users = await _userManager.Users.ToListAsync();
            return View(users);
        }

        public async Task<IActionResult> GetUser(string id)
        {
            var user = await _userManager.FindByIdAsync(id);

            if (user == null)
            {
                return NotFound();
            }

            return View(user);
        }

        public async Task<IActionResult> Edit(string id)
            {
                if (id == null)
                {
                    return NotFound();
                }

                var user = await _userManager.FindByIdAsync(id);

                if (user == null)
                {
                    return NotFound();
                }

                return View(user);
            }

            [HttpPost]
            [ValidateAntiForgeryToken]
            public async Task<IActionResult> Edit(string id, User user)
            {
                if (id != user.Id)
                {
                    return NotFound();
                }

                if (ModelState.IsValid)
                {
                    try
                    {
                        var existingUser = await _userManager.FindByIdAsync(id);
                        existingUser.UserName = user.UserName;
                        existingUser.Email = user.Email;
                        existingUser.Anonimo = user.Anonimo;
                        existingUser.Premium = user.Premium;
                        existingUser.Admin = user.Admin;
                        
                        await _userManager.UpdateAsync(existingUser);

                        return RedirectToAction(nameof(ListUsers));
                    }
                    catch (Exception)
                    {
                        ModelState.AddModelError("", "Ocorreu um erro ao salvar as informações do usuário.");
                    }
                }

                return View(user);
            }

            public async Task<IActionResult> Delete(string id)
            {
                if (id == null)
                {
                    return NotFound();
                }

                var user = await _userManager.FindByIdAsync(id);

                if (user == null)
                {
                    return NotFound();
                }

                return View(user);
            }

            [HttpPost, ActionName("DeleteConfirmed")]
            [ValidateAntiForgeryToken]
            public async Task<IActionResult> DeleteConfirmed(string id)
            {
                var user = await _userManager.FindByIdAsync(id);

                if (user == null)
                {
                    return NotFound();
                }

                await _userManager.DeleteAsync(user);

                return RedirectToAction(nameof(ListUsers));
            }


            
        }
}

