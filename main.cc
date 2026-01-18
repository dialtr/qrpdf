#include <cairo/cairo-pdf.h>
#include <cairo/cairo.h>
#include <qrencode.h>

#include <iostream>
#include <string>
#include <cstdlib>

// Google C++ Style Guide recommends using unnamed namespaces for internal helpers.
namespace {

constexpr double kPaperSizePts = 288.0;  // 4 inches * 72 points/inch
constexpr double kMarginPts = 72.0;       // 1.0 inch margin in points

// Encodes the given text into a QR code and renders it as a PDF file.
bool GenerateQrPdf(const std::string& text, const std::string& output_filename) {
  QRcode* qr = QRcode_encodeString(text.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
  if (!qr) {
    std::cerr << "Failed to encode QR code." << std::endl;
    return false;
  }

  cairo_surface_t* surface = cairo_pdf_surface_create(
      output_filename.c_str(), kPaperSizePts, kPaperSizePts);
  if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS) {
    std::cerr << "Failed to create Cairo PDF surface." << std::endl;
    QRcode_free(qr);
    return false;
  }

  cairo_t* cr = cairo_create(surface);

  // Set background to white
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_rectangle(cr, 0, 0, kPaperSizePts, kPaperSizePts);
  cairo_fill(cr);

  // Set foreground to black
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

  // Calculate scaling factors
  // We want to fit 'width' modules into 'kPaperSizePts' minus margins.
  const double draw_area = kPaperSizePts - 2 * kMarginPts;
  const double module_size = draw_area / qr->width;

  // Translate to start margin
  cairo_translate(cr, kMarginPts, kMarginPts);

  // Draw the modules
  for (int y = 0; y < qr->width; ++y) {
    for (int x = 0; x < qr->width; ++x) {
      // The least significant bit determines if the module is black.
      if (qr->data[y * qr->width + x] & 1) {
        cairo_rectangle(cr, x * module_size, y * module_size, module_size,
                        module_size);
        cairo_fill(cr);
      }
    }
  }

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  QRcode_free(qr);

  std::cout << "Successfully generated " << output_filename << std::endl;
  return true;
}

}  // namespace

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <URL>" << std::endl;
    return 1;
  }

  std::string url = argv[1];
  std::string output_file = "output.pdf";

  // Check if running under 'bazel run' and save to the workspace root if so.
  const char* workspace_dir = std::getenv("BUILD_WORKSPACE_DIRECTORY");
  if (workspace_dir) {
    output_file = std::string(workspace_dir) + "/" + output_file;
  }

  if (!GenerateQrPdf(url, output_file)) {
    return 1;
  }

  return 0;
}
