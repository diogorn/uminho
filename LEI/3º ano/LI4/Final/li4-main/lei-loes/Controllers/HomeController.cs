using lei_loes.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Microsoft.AspNetCore.Identity;
using lei_loes.Data;


namespace lei_loes.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly UserManager<User> _userManager;

        public HomeController(ILogger<HomeController> logger, UserManager<User> userManager)
        {
            _logger = logger;
            _userManager = userManager;
        }

         public async Task<IActionResult> Index()
          {
                var user = await _userManager.GetUserAsync(User);
                ViewBag.Admin = user != null && await _userManager.IsInRoleAsync(user, "Admin");
                if (user != null)
                {
                    ViewBag.Admin = user.Admin;
                }
                else
                {
                    ViewBag.Admin = false;
                }

                return View();
            }




        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
