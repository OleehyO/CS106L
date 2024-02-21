class Navbar extends HTMLElement {
    constructor() {
        super();
    }
    connectedCallback() {
        var currentPage = this.attributes.currentPage;
        if (typeof currentPage === "undefined") {
            currentPage = "";
        }
        else {
            currentPage = currentPage.value;
        }
        var highlightedStyle = "font-weight: 550;";
        this.innerHTML = `
        <nav class="navbar navbar-expand-sm navbar-dark mb-3">
            <a href="index.html" class="navbar-brand " style="font-family:Jost; color:white; font-size:1rem; font-weight:700; ">CS 106L</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
              </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <div class="navbar-nav">
                    <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" style="color: rgba(255, 255, 255, 1);${currentPage === "assignments" ? highlightedStyle : ""}">
                              assignments
                            </a>
                            <div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink">
                              <a class="dropdown-item" style="font-family:Jost;" href="assignment-setup">Assignment Setup</a>
                              <a class="dropdown-item" style="font-family:Jost;" href="assignment2.html">Assignment 1: WikiRacer </a>
                              <a class="dropdown-item" style="font-family:Jost;" href="assignment3.html">Assignment 2: STL HashMap</a>
                              </div>
                          </li>

                    <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle" href="#" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false" style="color: rgba(255, 255, 255, 1);">
                              resources
                            </a>
                            <div class="dropdown-menu" aria-labelledby="navbarDropdownMenuLink" style="margin-left=-3px;">
                              <a class="dropdown-item" style="font-family:Jost;" href="http://paperless.stanford.edu">Paperless Link (Submit Code)</a>
                              <a class="dropdown-item" style="font-family:Jost;" href="https://docs.google.com/document/d/1Y6r7U8Bz2sqAiV23kKpUS5uXQkga32X3ZFasHoKyq_8">Python to C++ Guide</a>
                              <a class="dropdown-item" style="font-family:Jost;" href="https://en.cppreference.com/w/">C++ Documentation</a>
                              <a class="dropdown-item" style="font-family:Jost;" href="https://edstem.org/us/courses/32292/discussion/">EdStem (for Enrolled Students)</a>
                              <a class="dropdown-item" style="font-family:Jost;" href="full_course_reader.pdf">Original 106L Course Reader</a>
                            </div>
                          </li>
                    <a href="index.html#calendar" class="nav-item nav-link" style="color: rgba(255, 255, 255, 1);">
                        schedule
                    </a>
                    <a href="policies.html" class="nav-item nav-link" style="color: rgba(255, 255, 255, 1);${currentPage === "policies" ? highlightedStyle : ""}">
                        policies
                    </a>
                </div>
            </div>
        </nav>
    `;
    }
}


customElements.define('navbar-component', Navbar);
