/**
* Template Name: MyResume
* Template URL: https://bootstrapmade.com/free-html-bootstrap-template-my-resume/
* Updated: Jun 29 2024 with Bootstrap v5.3.3
* Author: BootstrapMade.com
* License: https://bootstrapmade.com/license/
*/

(function() {
  "use strict";

  /**
   * Header toggle
   */
  const headerToggleBtn = document.querySelector('.header-toggle');

  function headerToggle() {
    document.querySelector('#header').classList.toggle('header-show');
    headerToggleBtn.classList.toggle('bi-list');
    headerToggleBtn.classList.toggle('bi-x');
  }
  headerToggleBtn.addEventListener('click', headerToggle);

  /**
   * Hide mobile nav on same-page/hash links
   */
  document.querySelectorAll('#navmenu a').forEach(navmenu => {
    navmenu.addEventListener('click', () => {
      if (document.querySelector('.header-show')) {
        headerToggle();
      }
    });

  });

  /**
   * Toggle mobile nav dropdowns
   */
  document.querySelectorAll('.navmenu .toggle-dropdown').forEach(navmenu => {
    navmenu.addEventListener('click', function(e) {
      e.preventDefault();
      this.parentNode.classList.toggle('active');
      this.parentNode.nextElementSibling.classList.toggle('dropdown-active');
      e.stopImmediatePropagation();
    });
  });

  /**
   * Scroll top button
   */
  let scrollTop = document.querySelector('.scroll-top');

  function toggleScrollTop() {
    if (scrollTop) {
      window.scrollY > 100 ? scrollTop.classList.add('active') : scrollTop.classList.remove('active');
    }
  }
  scrollTop.addEventListener('click', (e) => {
    e.preventDefault();
    window.scrollTo({
      top: 0,
      behavior: 'smooth'
    });
  });

  window.addEventListener('load', toggleScrollTop);
  document.addEventListener('scroll', toggleScrollTop);

  /**
   * Animation on scroll function and init
   */
  function aosInit() {
    AOS.init({
      duration: 600,
      easing: 'ease-in-out',
      once: true,
      mirror: false
    });
  }
  window.addEventListener('load', aosInit);

  /**
   * Init typed.js
   */
  const selectTyped = document.querySelector('.typed');
  if (selectTyped) {
    let typed_strings = selectTyped.getAttribute('data-typed-items');
    typed_strings = typed_strings.split(',');
    new Typed('.typed', {
      strings: typed_strings,
      loop: true,
      typeSpeed: 100,
      backSpeed: 50,
      backDelay: 2000
    });
  }
  /**
   * Navmenu Scrollspy
   */
  let navmenulinks = document.querySelectorAll('.navmenu a');

  function navmenuScrollspy() {
    navmenulinks.forEach(navmenulink => {
      if (!navmenulink.hash) return;
      let section = document.querySelector(navmenulink.hash);
      if (!section) return;
      let position = window.scrollY + 200;
      if (position >= section.offsetTop && position <= (section.offsetTop + section.offsetHeight)) {
        document.querySelectorAll('.navmenu a.active').forEach(link => link.classList.remove('active'));
        navmenulink.classList.add('active');
      } else {
        navmenulink.classList.remove('active');
      }
    })
  }
  window.addEventListener('load', navmenuScrollspy);
  document.addEventListener('scroll', navmenuScrollspy);

  const popup = document.getElementById('popup');
  const popupTitle = document.getElementById('popup-title');
  const popupDescription = document.getElementById('popup-description');
  const popupSkills = document.getElementById('popup-skills');
  const popupImage = document.getElementById('popup-image');
  const popupLink = document.getElementById('popup-link');
  const viewButtons = document.querySelectorAll('.view-btn');
  const closeBtn = document.querySelector('.popup .close-btn');
  
  // Ouvrir la pop-up avec des données dynamiques
  viewButtons.forEach(button => {
    button.addEventListener('click', () => {
      const title = button.getAttribute('data-title');
      const description = button.getAttribute('data-description');
      const image = button.getAttribute('data-image');
      const skills = button.getAttribute('data-skills');
      const link = button.getAttribute('data-link');
  
      // Mettre à jour le contenu de la pop-up
      popupTitle.textContent = title;
      popupDescription.textContent = description;
      popupImage.src = image;
  
      // Gérer la liste des compétences
      popupSkills.innerHTML = ""; // Réinitialiser la liste
      if (skills) {
        skills.split(',').forEach(skill => {
          const li = document.createElement('li');
          li.textContent = skill.trim();
          popupSkills.appendChild(li);
        });
      }
  
      // Mettre à jour le lien "Consulter"
      popupLink.href = link;
      popupLink.style.display = link ? 'inline-block' : 'none'; // Cacher si aucun lien
  
      popup.style.display = 'flex';
      document.body.style.overflow = 'hidden'; // Empêcher le scroll
    });
  });
  
  // Fermer la pop-up
  closeBtn.addEventListener('click', () => {
    popup.style.display = 'none';
    document.body.style.overflow = ''; // Rétablir le scroll
  });
  
  // Fermer la pop-up en cliquant en dehors
  popup.addEventListener('click', event => {
    if (event.target === popup) {
      popup.style.display = 'none';
      document.body.style.overflow = ''; // Rétablir le scroll
    }
  });

// Gestion du filtrage
const filterButtons = document.querySelectorAll('.portfolio-nav .btn');
const portfolioCards = document.querySelectorAll('.portfolio-card');

filterButtons.forEach(button => {
  button.addEventListener('click', () => {
    const filter = button.getAttribute('data-filter');

    // Désactiver tous les boutons et activer uniquement le bouton cliqué
    filterButtons.forEach(btn => {
      btn.classList.remove('active', 'btn-primary'); // Retire les classes "active" et "btn-primary"
      btn.classList.add('btn-outline-primary'); // Applique la classe "btn-outline-primary" par défaut
    });
    button.classList.add('active', 'btn-primary'); // Ajoute les classes pour le bouton actif
    button.classList.remove('btn-outline-primary'); // Retire la classe "btn-outline-primary" du bouton actif

    // Filtrer les cartes
    portfolioCards.forEach(card => {
      if (filter === 'all' || card.getAttribute('data-category') === filter) {
        card.style.display = 'flex';
      } else {
        card.style.display = 'none';
      }
    });
  });
});

})();