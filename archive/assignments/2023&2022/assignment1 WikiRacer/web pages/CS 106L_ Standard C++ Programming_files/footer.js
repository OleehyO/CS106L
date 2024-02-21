class Footer extends HTMLElement {
    constructor() {
        super();
    }
    connectedCallback() {
        this.innerHTML = `
        <div class="row" style="position:absolute; bottom: 0px; width: 100%; text-align: center;">
        <div class="col-lg-12">
            <footer>
              <small>© 2022. Created by Haven Whitney and Sarah McCarthy.</small>
            </footer>
        </div>
    </div>
    `;
    }
}


customElements.define('footer-component', Footer);
