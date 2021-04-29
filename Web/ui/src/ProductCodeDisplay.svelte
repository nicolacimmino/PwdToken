<script>
    import moment from "moment"
    import "./style.css"

    export let productCode

    function getProductCodeLetters() {
        return [...productCode];
    }

    function getSoftwareVersion() {
        return productCode.substring(0, 3);
    }

    function getKeypadType() {
        const keyPadTypes = {
            "B": "Binary",
            "M": "Morse",
            "N": "None"
        }

        const keypadCode = productCode.substring(3, 4);

        if (keyPadTypes[keypadCode] === undefined) {
            return "?";
        }

        return keyPadTypes[keypadCode];
    }

    function getHardwareRevision() {
        const hardwareRevisionCode = productCode.substring(5, 6);

        const hardwareRevision = hardwareRevisionCode.toUpperCase().charCodeAt(0) - "A".charCodeAt(0);

        var wiredRevisionCodes = /^[a-z]+$/;
        const isWired = (hardwareRevisionCode.match(wiredRevisionCodes));

        return hardwareRevisionCode + (isWired ? " (wired)" : "");
    }

    function getManufacturingMonth() {
        const monthCode = productCode.substring(6, 7);

        const monthNumber = parseInt("0x" + monthCode) - 1;

        return moment().month(monthNumber).format("MMM");
    }

    function getManufacturingYear() {
        const yearCode = parseInt(productCode.substring(7, 8));

        return 2020 + yearCode;
    }

    function getSecureBootloader() {
        const futherOptionsCodes = productCode.substring(9);

        return futherOptionsCodes.indexOf("S") !== -1;
    }
</script>

<div class="productCodeDisplay card">
    <div class="productCode">
        <div class="productElements">
            {#each getProductCodeLetters() as letter }
                <div>
                    {letter}
                </div>
            {/each}
        </div>
    </div>

    <div>
        SW Version
    </div>
    <div>
        {getSoftwareVersion()}
    </div>

    <div>
        Keypad Type
    </div>
    <div>
        {getKeypadType()}
    </div>

    <div>
        HW Revision
    </div>
    <div>
        {getHardwareRevision()}
    </div>

    <div>
        Manufacturing Date
    </div>
    <div>
        {getManufacturingMonth()} {getManufacturingYear()}
    </div>

    <div>
        Secure Bootloader
    </div>
    <div>
        {getSecureBootloader() ? "Yes" : "No"}
    </div>

    <svg id="linesCanvas" width="500" height="500">
        <line x1="50" y1="50" x2="350" y2="350" stroke="black"/>
    </svg>
</div>


<style>
    .productCodeDisplay {
        position: relative;
        font-family: "Courier New", sans-serif;
        width: 800px;
        margin: auto;
        display: grid;
        grid-template-columns: 200px 400px;
        grid-template-rows: 1fr 1fr 1fr 1fr 1fr 1fr;
        gap: 0px 0px;
        grid-template-areas:
            "productCode productCode"
            ". . "
            ". . "
            ". . "
            ". . "
            ". . ";
    }

    .productCode {
        grid-area: productCode;
        text-align: center;
        font-weight: bold;
    }

    .productElements {
        display: grid;
        grid-template-rows: 1fr;
        grid-template-columns: 1fr;
        grid-template-areas:
            ". . . . . . . .";
    }

    .productElements div {
        border: black dotted 1px;
    }

    .productCodeDisplay #linesCanvas {
        position: relative;
        top: 0;
        left: 0;
    }
</style>