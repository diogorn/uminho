using Microsoft.EntityFrameworkCore;
using lei_loes.Models;


using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;


namespace lei_loes.Data
{
    public class ApplicationDbContext : IdentityDbContext<User>
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
                 : base(options)
        { }
        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);

            // Relação entre Leilao e Carro
            builder.Entity<LeilaoModel>()
                    .HasOne<CarroModel>()
                    .WithMany()
                    .HasForeignKey(p => p.Carro_CarroID);


            // Relação entre Lance e Leilao
            builder.Entity<LanceModel>()
                    .HasOne<LeilaoModel>()
                    .WithMany()
                    .HasForeignKey(p => p.Leilao_LeilaoID);
            builder.Entity<User>()
                .HasKey(u => u.Id);
        }

        public DbSet<CarroModel> CarroModel { get; set; }
        public DbSet<BilhetePremiumModel> BilhetePremiumModel { get; set; }
        public DbSet<LeilaoModel> LeilaoModel { get; set; }
        public DbSet<LanceModel> LanceModel { get; set; }
    }
    public class UserEntityConfiguration : IEntityTypeConfiguration<User>
    {
        void IEntityTypeConfiguration<User>.Configure(EntityTypeBuilder<User> builder)
        {
            builder.HasKey(u => u.Id);

        }
    }
}
