async function runJailbreak() {
    window.jb_in_progress = true;
    window.jb_started = true;

    let postjb = document.getElementById("post-jb-view");
    postjb.style.opacity = "0";
    postjb.style.pointerEvents = "none";

    document.getElementById("run-jb-parent").style.opacity = "0";
    await sleep(500);
    document.getElementById("run-jb-parent").style.display = "none";
    document.getElementById("jb-progress").style.opacity = "1";
    await sleep(500);

    create_payload_buttons();
    setTimeout(() => {
        poc();
    }, 100);
}

function onload_setup() {

    create_redirector_buttons();

    document.documentElement.style.overflowX = 'hidden';
    let center_view = document.getElementById("center-view");

    let isTransitionInProgress = false;

    center_view.style.transition = "left 0.4s ease, opacity 0.25s ease";
    center_view.style.pointerEvents = "auto";
    center_view.style.opacity = "1";
}

async function switch_to_post_jb_view() {
    // should already be none but just in case
    document.getElementById("run-jb-parent").style.display = "none";

    document.getElementById("jb-progress").style.opacity = "0";
    await sleep(1000);
    document.getElementById("jb-progress").style.display = "none";

    document.getElementById("post-jb-view").style.opacity = "0";
    document.getElementById("post-jb-view").classList.add("opacity-transition");
    document.getElementById("post-jb-view").style.display = "flex";
    document.getElementById("post-jb-view").style.opacity = "1";

    document.getElementById("credits").style.opacity = "0";
    document.getElementById("credits").style.display = "none";

}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function create_payload_buttons() {
    window.local_payload_queue = [];
    for (let i = 0; i < payload_map.length; i++) {
        let btn = document.createElement("a");
        btn.id = "payload-" + i;
        btn.className = "btn mx-auto";
        btn.tabIndex = "0";
        btn.onclick = async () => {
            showToast(payload_map[i].displayTitle + " added to queue.", 1000);
            window.local_payload_queue.push(payload_map[i]);
        };

        let btn_child = document.createElement("p");
        btn_child.className = "payload-name";
        btn_child.innerHTML = payload_map[i].displayTitle;
        btn.appendChild(btn_child);

        let btn_child2 = document.createElement("p");
        btn_child2.className = "payload-description";
        btn_child2.innerHTML = payload_map[i].description;
        btn.appendChild(btn_child2);

        let btn_child3 = document.createElement("p");
        btn_child3.className = "payload-author";
        btn_child3.innerHTML = "v" + payload_map[i].version;
        btn.appendChild(btn_child3);

        document.getElementById("payloads-list").appendChild(btn);

    }

}

function showToast(message) {
    const toastContainer = document.getElementById('toast-container');
    const toast = document.createElement('div');
    toast.className = 'toast';
    toast.textContent = message;

    toastContainer.appendChild(toast);

    // Trigger reflow and enable animation
    toast.offsetHeight;

    toast.classList.add('show');

    setTimeout(() => {
        toast.classList.add('hide');
        toast.addEventListener('transitionend', () => {
            toast.remove();
        });
    }, 2000);
}
