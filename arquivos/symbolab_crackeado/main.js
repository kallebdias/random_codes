var code = `window.onload = function(){
    /* set subscription params */
    if (typeof(SYSTEPS) != 'undefined') { SYSTEPS.subscribed = true }
    if (typeof(SOLUTIONS) != 'undefined') { SOLUTIONS.subscribed = true }
    if (typeof(SYMBOLAB) != 'undefined') { SYMBOLAB.params.subscribed = true }
    if (typeof(SYPRACTICE) != 'undefined') { SYPRACTICE.subscribed = true }
    isUserLoggedIn = function() { return true }

    /* remove popup when verify solution box is clicked */
    if ($("#click-capture")) {
        // add the class name to the click capture to prevent blocking
        $("#click-capture").addClass("click-capture-subscribed")
    }

    /* improvements to dark mode */
    fixDarkMode = function() {
        // check if dark mode style element is on the page
        if($("#invert-style").length > 0) {
            // replace the styling element with better styling
            var invertStyle = $("#invert-style")[0].innerHTML
            $("#invert-style")[0].remove()
            document.head.insertAdjacentHTML("beforeend",
                '<style type="text/css" id="invert-style">' +
                invertStyle +
                \`img,
                #HomeTopNav svg,
                button.btn.btn-large.btn-custom.search,
                button.verify-button,
                li#solutionsTopNav a span,
                span.bloggerIcon,
                a.show-hide-button.show-hide-plot.print-hide,
                a.stepsPracticeLink span,
                .m2u>li>a.active,
                .m3u>li>a.active,
                li a.nl-leftMenu span,
                .nl-feedback.nl-redText.print-hide span {
                    filter: invert(1);
                }

                img.open,
                img.close,
                ul.solution-examples li svg,
                a.nl-leftMenu.active span {
                    filter: invert(0);
                }

                button.btn.btn-large.btn-custom.search {
                    border: 1px solid black;
                }

                div#nl-subNav {
                    background-color: rgba(220, 220, 220, 1);
                }

                a.nl-topMenu span,
                a.nl-topMenu.active .nl-topSubMenu span,
                #nl-subNav ul li .nl-topSubMenu a:hover span {
                    color: #000000;
                }

                a.nl-topMenu.active span,
                #nl-subNav ul li a:hover span {
                    color: #ffffff;
                }

                @-moz-document url-prefix() {
                    body {
                        background-color: #111111;
                    }
                }</style>\`)
        }
    };

    // fix dark mode when the page loads
    fixDarkMode()

    /* overwrite the toggle function to fix dark mode at end */
    var oldLightsOut = lightsOut;
    lightsOut = function() {
        // call the original lightsOut function
        oldLightsOut()
        // fix dark mode
        fixDarkMode()
    }
}`

// make sure the code runs before the subscription status is checked
document.documentElement.setAttribute("onreset", code)
document.documentElement.dispatchEvent(new CustomEvent("reset"))
document.documentElement.removeAttribute("onreset")